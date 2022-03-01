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

#define MIN(a, b) a < b ? a : b

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t wkgrp_sz = 1024; // OPTIMIZATION: Try different workgroup sizes
constexpr size_t num_wkgrps =
    MIN(wkgrp_sz, dataSize / wkgrp_sz); // OPTIMIZATION: Use more workgroups

/* ---------------------------------------------------------------------------*/
/**
 *  \brief:      A function that reduces an array in local memory into a single
 *               value at a[0].
 *
 * \param:       a        Local accessor of dimension wkgrp_sz
 * \param:       item
 * \param:       localIdx
 */
/* ---------------------------------------------------------------------------*/
template <typename T, size_t wkgrp_sz>
inline void // OPTIMIZATION: using inline
workgroup_reduce_local_mem(sycl::accessor<T, 1, sycl::access::mode::read_write,
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
  T *devPtrB =
      sycl::malloc_device<T>(num_wkgrps, q); // Holds intermediate values

  q.memcpy(devPtrA, a, sizeof(T) * dataSize).wait();

  auto my_nd =
      sycl::nd_range(sycl::range(num_wkgrps * wkgrp_sz), sycl::range(wkgrp_sz));

  q.submit([&](sycl::handler &cgh) {
     sycl::accessor<T, 1, sycl::access_mode::read_write,
                    sycl::access::target::local>
         local_mem(wkgrp_sz, cgh);

     cgh.parallel_for(my_nd, [=](sycl::nd_item<1> item) {
       auto localIdx = item.get_local_linear_id();
       auto globalIdx = item.get_global_linear_id();
       auto globalRange = item.get_global_range(0);

       local_mem[localIdx] = 0;

       auto arrayIdx = globalIdx;

       // Accumulating thread local reductions into local memory
       // OPTIMIZATION: coalesced memory access
       while (arrayIdx < dataSize) {
         local_mem[localIdx] += devPtrA[arrayIdx];
         arrayIdx += globalRange;
       }
       item.barrier();
       workgroup_reduce_local_mem<T, wkgrp_sz>(local_mem, item, localIdx);
       devPtrB[item.get_group_linear_id()] = local_mem[0];
     });
   }).wait();
  
  // OPTIMIZATION: Using parallel_for instead of single_task
  q.submit([&](sycl::handler &cgh) {
     // Declaring a local accessor
     sycl::accessor<T, 1, sycl::access_mode::read_write,
                    sycl::access::target::local>
         local_mem(wkgrp_sz, cgh);

     // Second kernel executed by a single work group
     auto second_nd =
         sycl::nd_range(sycl::range(wkgrp_sz), sycl::range(wkgrp_sz));
     
     // Reduce smaller array into a single value
     cgh.parallel_for(second_nd, [=](sycl::nd_item<1> item) {
       auto localIdx = item.get_local_linear_id();
       local_mem[localIdx] = 0;

       auto arrayIdx = localIdx;
       // Accumulating thread local reductions into local memory
       while (arrayIdx < num_wkgrps) {
         local_mem[localIdx] += devPtrB[arrayIdx];
         arrayIdx += wkgrp_sz;
       }
       item.barrier();
       workgroup_reduce_local_mem<T, wkgrp_sz>(local_mem, item, localIdx);
       devPtrB[0] = local_mem[0];
     });
   }).wait();

  T devAns = 0;
  q.memcpy(&devAns, devPtrB, sizeof(T));

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << '\n';

  sycl::free(devPtrA, q);
  sycl::free(devPtrB, q);
}
