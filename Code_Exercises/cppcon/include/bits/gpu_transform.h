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

#ifndef __GPU_TRANSFORM_H__
#define __GPU_TRANSFORM_H__

#include <functional>
#include <iterator>
#include <thread>
#include <utility>
#include <vector>

#include <bits/sycl_policy.h>
#include <CL/sycl.hpp>

namespace cppcon {

template <class ContiguousIt, class UnaryOperation, typename KernelName>
ContiguousIt transform(sycl_execution_policy_t<KernelName> policy,
                       ContiguousIt first, ContiguousIt last,
                       ContiguousIt d_first, UnaryOperation unary_op) {
  using value_t = typename std::iterator_traits<ContiguousIt>::value_type;

  /* If the input range is empty then return the output iterator */
  if (first == last) return d_first;

  /* Wrap all SYCL API calls with a try-catch block to ensure you handle
   * exceptions from the SYCL runtime */
  try {
    /* Retrieve the SYCL queue that the algorithm will execute on */
    auto q = policy.get_queue();

    /* Determine the data size of the input range */
    size_t dataSize = std::distance(first, last);

    /* Construct a buffer for managing the input range and call set_final_data
     * in order to stop the runtime from copying back on destruction */
    cl::sycl::buffer<value_t, 1> inputBuf(first, last);
    inputBuf.set_final_data(nullptr);

    /* Construct a buffer for managing the output range, by passing the address
     * of the first element in the range */
    cl::sycl::buffer<value_t, 1> outputBuf(std::addressof(*d_first), dataSize);

    /* Submit a command group to the queue */
    q.submit([&](cl::sycl::handler& cgh) {
      /* Construct the range that the SYCL kernel will execute over, where the
       * global range is the data size */
      auto globalRange = cl::sycl::range<1>(dataSize);

      /* Construct a buffer accessor with read access for the buffer that
       * manages the input range */
      auto inputAcc =
          inputBuf.template get_access<cl::sycl::access::mode::read>(cgh);
      /* Construct a buffer accessor with discard_read_write access for the
       * buffer that manages the output range */
      auto outputAcc =
          outputBuf.template get_access<cl::sycl::access::mode::discard_write>(
              cgh);

      /* Launch a SYCL kernel using the range constructed above and taking a
       * lambda with an id parameter */
      cgh.parallel_for<KernelName>(globalRange, [=](cl::sycl::id<1> idx) {
        /* Read the element in global memory of the input range at the index of
         * the current work-item, pass it to the unary operator and write the
         * result to the element in global memory of the output range at the
         * index of the current work-item */
        outputAcc[idx] = unary_op(inputAcc[idx]);
      });
    });

    /* Wait and throw to catch any exception that have been thrown by the SYCL
     * runtime */
    q.wait_and_throw();
  } catch (cl::sycl::exception e) {
    std::cout << "SYCL exception caught: " << e.what() << std::endl;
  }

  /* Return the output iterator */
  return d_first;
}

}  // namespace cppcon

#endif  // __GPU_TRANSFORM_H__
