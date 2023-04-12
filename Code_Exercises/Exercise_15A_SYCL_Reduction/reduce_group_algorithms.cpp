/*
 * This code performs a reduce operation over an array.
 *
 * The reduction happens in two steps:
 *
 * 1. Reduce over a workgroup with reduce_over_group
 * 2. Reduce globally using a global atomic_ref
 *
 */

#include <sycl/sycl.hpp>

#define MIN(a, b) a < b ? a : b

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;

int main(int argc, char *argv[]) {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devA = sycl::malloc_device<T>(dataSize, q);
  T *devReduced = sycl::malloc_device<T>(1, q); // Holds reduction output

  q.memcpy(devA, a, sizeof(T) * dataSize).wait();
  q.fill(devReduced, 0, 1).wait();

  auto myNd = sycl::nd_range(sycl::range(dataSize), sycl::range(workGroupSize));

  q.submit([&](sycl::handler &cgh) {
     sycl::local_accessor<T, 1> localMem(workGroupSize, cgh);

     cgh.parallel_for(myNd, [=](sycl::nd_item<1> item) {
       auto localIdx = item.get_local_linear_id();
       auto globalIdx = item.get_global_linear_id();
       auto globalRange = item.get_global_range(0);

       localMem[localIdx] = 0;

       // Accumulating thread local reductions into local memory
       for (auto i = globalIdx; i < dataSize; i += globalRange) {
         localMem[localIdx] += devA[i];
       }

       T groupReduction = sycl::reduce_over_group(
           item.get_group(), localMem[localIdx], sycl::plus<>());

       if (localIdx == 0)
         sycl::atomic_ref<T, sycl::memory_order_relaxed,
                          sycl::memory_scope_work_group,
                          sycl::access::address_space::global_space>(
             devReduced[0])
             .fetch_add(groupReduction);
     });
   }).wait();

  T devAns = 0;
  q.memcpy(&devAns, devReduced, sizeof(T));

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << '\n';

  sycl::free(devA, q);
  sycl::free(devReduced, q);
}
