/*
Copyright 2018 Gordon Brown

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __GPU_TRANSFORM_REDUCE_H__
#define __GPU_TRANSFORM_REDUCE_H__

#include <functional>
#include <iterator>
#include <thread>
#include <utility>
#include <vector>

#include <bits/sycl_policy.h>
#include <CL/sycl.hpp>

namespace cppcon {

template <class ContiguousIt, class T, class BinaryOperation,
          class UnaryOperation, typename KernelName>
T transform_reduce(sycl_execution_policy_t<KernelName> policy,
                   ContiguousIt first, ContiguousIt last, T init,
                   BinaryOperation binary_op, UnaryOperation unary_op) {
  using value_t = typename std::iterator_traits<ContiguousIt>::value_type;

  /* If the input range is empty then return the initial value */
  if (first == last) return init;

  T result{};

  /* Wrap all SYCL API calls with a try-catch block to ensure you handle
   * exceptions from the SYCL runtime */
  try {
    /* Retrieve the SYCL queue that the algorithm will execute on */
    auto q = policy.get_queue();

    /* Retrieve the work-group size of the device that the algorithm will
     * execute on */
    auto workGroupSize = policy.get_work_group_size();

    /* Determine the data size of the input range */
    size_t dataSize = std::distance(first, last);

    /* Construct a buffer for managing the input range and call set_final_data
     * in order to stop the runtime from copying back on destruction */
    cl::sycl::buffer<value_t, 1> inputBuf(first, last);
    inputBuf.set_final_data(nullptr);

    /* Specify how many iterations of the reduction should perform the transform
     * operation */
    int numTransforms = 1;

    /* Loop over the same SYCL kernel until it yeilds a single reduction value
     */
    do {
      /* Submit a command group to the queue */
      q.submit([&](cl::sycl::handler& cgh) {
        /* Construct the nd-range that the SYCL kernel will execute over, where
         * the global range is the data size and the local range is the minimum
         * of the data size and work-group size */
        auto globalRange =
            cl::sycl::range<1>(std::max(dataSize, workGroupSize));
        auto localRange = cl::sycl::range<1>(std::min(dataSize, workGroupSize));
        auto ndRange = cl::sycl::nd_range<1>(globalRange, localRange);

        /* Construct a buffer accessor for the buffer that manages the input
         * range */
        auto inputAcc =
            inputBuf.template get_access<cl::sycl::access::mode::read_write>(
                cgh);

        /* Construct a local accessor for allocating memory for each work-group
         * for storing the intermediate partial reductions */
        cl::sycl::accessor<value_t, 1, cl::sycl::access::mode::read_write,
                           cl::sycl::access::target::local>
            scratchPad(localRange, cgh);

        /* Launch a SYCL kernel using the nd-range constructed above and taking
         * a lambda with an nd-item parameter */
        cgh.parallel_for<KernelName>(ndRange, [=](cl::sycl::nd_item<1> ndItem) {
          /* Retrieve the global id, local id and group id of the current
           * iteration of the SYCL kernel */
          size_t globalId = ndItem.get_global_id(0);
          size_t localId = ndItem.get_local_id(0);
          size_t groupId = ndItem.get_group(0);

          /* Copy each element of the input range from global memory into the
           * local memory of it's work-group, applying the unary operator in the
           * case of the first reduction */
          if (numTransforms) {
            scratchPad[localId] = unary_op(inputAcc[globalId]);
          } else {
            scratchPad[localId] = inputAcc[globalId];
          }

          /* Insert a work-group barrier to ensure that all elements of the
           * input range have been copied from global memory to local memory
           * before continuing */
          ndItem.barrier(cl::sycl::access::fence_space::local_space);

          /* Loop over the size of the work-group creating an offset to the
           * midpoint each time until you reach zero */
          for (size_t offset = localRange[0] / 2; offset > 0; offset /= 2) {
            /* Mask the segment of the work-group that you want to write back
             * partial reductions to local memory */
            if (localId < offset) {
              /* Read the elements in local memory at the indexes of the current
               * work-item and the respective work-item on the other side of the
               * midpoint, pass those to the binary operator, and then write the
               * result to the element of local memory at the index of the
               * current work-item */
              scratchPad[localId] =
                  binary_op(scratchPad[localId], scratchPad[localId + offset]);
            }
            /* Insert a work-group barrier to ensure that each partial reduction
             * is complete before the work-group continues */
            ndItem.barrier(cl::sycl::access::fence_space::local_space);
          }

          /* Once the work-group loop is complete you have a single partial
           * reduction in each work-group, we copy this back to global memory
           * using the current group id to create a new contiguous range of
           * elements that can be used by the next kernel */
          if (localId == 0) {
            inputAcc[groupId] = scratchPad[localId];
          }
        });
      });
      /* After each SYCL kernel you will have a partial result contiguously at
       * the begining of the buffer for each work-group that was executed, we
       * can calculate the size of these partial results by dividing the data
       * size by the work group size, if this becomes zero we are done */
      dataSize = dataSize / workGroupSize;
      numTransforms = 0;
    } while (dataSize > 1);

    /* Once the outer loop is complete you have a partial reduction for the full
     * input range */
    {
      /* Create a host accessor to read back the partial reduction value for the
       * full input range and assign it to the result variable */
      auto inputHostAcc =
          inputBuf.template get_access<cl::sycl::access::mode::read>();
      result = inputHostAcc[0];
    }

    /* Wait and throw to catch any exception that have been thrown by the SYCL
     * runtime */
    q.wait_and_throw();
  } catch (cl::sycl::exception e) {
    std::cout << "SYCL exception caught: " << e.what() << std::endl;
  }

  /* Pass the partial reduction from the full input range and the initial value
   * to the binary operator and return the result */
  return binary_op(init, result);
}

}  // namespace cppcon

#endif  // __GPU_TRANSFORM_REDUCE_H__
