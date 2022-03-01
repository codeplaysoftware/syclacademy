/* 
 * This code performs a reduce operation over an array.
 * We use two separate kernels, in order to achieve a global
 * device synchronization.
 * 
 * Kernel 1:
 * Reduce the array into a smaller array of dimension num_wkgroups
 * 
 * Kernel 2:
 * Reduce the smaller array into a single value 
 * 
 * Use optimization principles from slides in order to make code run faster.
 * 
 */
 

#include <CL/sycl.hpp>

using T = float;

constexpr size_t dataSize = 16'384;
constexpr size_t wkgrp_sz =
    32; // TODO check which wkgrp_sz is optimal for this problem
constexpr size_t num_wkgrps =
    2; // TODO does 2 active workgroups seem like an efficient use of hardware?

/* ---------------------------------------------------------------------------*/
/**
 *  \brief:      A function that reduces an array in local memory into a single
 *               value at a[0].
 *
 *               TODO what simple keyword may improve performance?
 *
 * \param:       a        Local accessor of dimension wkgrp_sz
 * \param:       item
 * \param:       localIdx
 */
/* ---------------------------------------------------------------------------*/
template <typename T, size_t wkgrp_sz>
void workgroup_reduce_local_mem(
    sycl::accessor<T, 1, sycl::access::mode::read_write,
                   sycl::access::target::local>
        a,
    sycl::nd_item<1> &item, size_t localIdx) {
#pragma unroll
  for (auto i = 1024; i >= 2; i /= 2) {
    if (wkgrp_sz >= i) {
      if (localIdx < i / 2)
        a[localIdx] += a[localIdx + i / 2];
      item.barrier();
    }
  }
}

int main() {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devPtrA = sycl::malloc_device<T>(dataSize, q);
  T *devPtrB = sycl::malloc_device<T>(num_wkgrps, q);

  q.memcpy(devPtrA, a, sizeof(T) * dataSize).wait();

  auto my_nd =
      sycl::nd_range(sycl::range(num_wkgrps * wkgrp_sz), sycl::range(wkgrp_sz));

  q.submit([&](sycl::handler &cgh) {
     // Declaring a local accessor
     sycl::accessor<T, 1, sycl::access_mode::read_write,
                    sycl::access::target::local>
         local_mem(wkgrp_sz, cgh);

     // Kernel to reduce array into a smaller array of
     // dimension <num_wkgroups>
     cgh.parallel_for(my_nd, [=](sycl::nd_item<1> item) {
       auto localIdx = item.get_local_linear_id();
       auto globalIdx = item.get_global_linear_id();
       auto globalRange = item.get_global_range(0);

       local_mem[localIdx] = 0;

       auto num_to_reduce_per_work_item =
           dataSize / globalRange; // This must divide

       auto array_idx = globalIdx * num_to_reduce_per_work_item;

       // Accumulating thread local reductions into local memory
       // TODO what does this memory access pattern look like? Are adjacent
       // threads accessing adjacent spaces in memory?
       while (array_idx < (globalIdx + 1) * num_to_reduce_per_work_item) {
         local_mem[localIdx] += devPtrA[array_idx++];
       }
       item.barrier();
       workgroup_reduce_local_mem<T, wkgrp_sz>(local_mem, item, localIdx);
       devPtrB[item.get_group_linear_id()] = local_mem[0];
     });
   }).wait();

  // Kernel to reduce smaller array into final value at devPtrA[0]
  // TODO if num_wkgrps is large, could we do this with a parallel_for?
  q.single_task([=]() {
     for (auto i = 1; i < num_wkgrps; i++)
       devPtrB[0] += devPtrB[i];
   }).wait();

  T devAns = 0;
  q.memcpy(&devAns, devPtrB, sizeof(T));
  
  T serialAns = 0;
  for (auto i=0;i<dataSize;i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << '\n';
  
  sycl::free(devPtrA, q);
  sycl::free(devPtrB, q);
}
