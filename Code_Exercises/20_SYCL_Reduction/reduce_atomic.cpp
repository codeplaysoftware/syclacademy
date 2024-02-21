/*
 * This code performs a reduce operation over an array.
 *
 * There are two implementations of the reduction using atomics:
 *
 * 1. Reduction where all values are naively reduced into global memory using
 *    an atomic add operation.
 *
 * 2. A reduction comprised of two atomic add operations:
 *        a. Reduce over a workgroup with a local memory atomic
 *        b. Reduce globally using a global atomic_ref
 *
 */

#include <benchmark.h>
#include <sycl/sycl.hpp>

template <typename T> constexpr T my_min(T a, T b) { return a < b ? a : b; }

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;
constexpr int numIters = 100;

int main(int argc, char *argv[]) {

  T a[dataSize];
  T devAns[2] = {0, 0};

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devA = sycl::malloc_device<T>(dataSize, q);
  T *devReduced = sycl::malloc_device<T>(1, q); // Holds intermediate values

  T zeroVal = 0;
  auto e1 = q.memcpy(devA, a, sizeof(T) * dataSize);
  auto e2 = q.memcpy(devReduced, &zeroVal, sizeof(T));

  auto myNd = sycl::nd_range(sycl::range(dataSize), sycl::range(workGroupSize));

  util::benchmark(
      [&]() {
        q.submit([&](sycl::handler &cgh) {
           cgh.depends_on({e1, e2});

           cgh.parallel_for(myNd, [=](sycl::nd_item<1> item) {
             auto globalIdx = item.get_global_linear_id();

             sycl::atomic_ref<T, sycl::memory_order_relaxed,
                              sycl::memory_scope_device>(devReduced[0])
                 .fetch_add(devA[globalIdx]);
           });
         }).wait();
      },
      numIters, "Reduction using only global atomics");

  auto e3 = q.memcpy(&devAns[0], devReduced, sizeof(T));
  q.memcpy(devReduced, &zeroVal, sizeof(T), e3).wait();

  util::benchmark(
      [&]() {
        q.submit([&](sycl::handler &cgh) {
           cgh.depends_on({e1, e2});
           sycl::local_accessor<T, 1> localMem(workGroupSize, cgh);
           sycl::local_accessor<T, 1> localReduction(1, cgh);

           cgh.parallel_for(myNd, [=](sycl::nd_item<1> item) {
             auto localIdx = item.get_local_linear_id();
             auto globalIdx = item.get_global_linear_id();
             auto globalRange = item.get_global_range(0);

             if (localIdx == 0)
               localReduction[0] = 0;

             item.barrier();

             // Accumulating thread local reductions into local memory
             localMem[localIdx] = devA[globalIdx];

             // Work group atomic add into local mem
             sycl::atomic_ref<T, sycl::memory_order_relaxed,
                              sycl::memory_scope_work_group,
                              sycl::access::address_space::local_space>(
                 localReduction[0])
                 .fetch_add(localMem[localIdx]);

             item.barrier();

             if (localIdx == 0)
               sycl::atomic_ref<T, sycl::memory_order_relaxed,
                                sycl::memory_scope_device,
                                sycl::access::address_space::global_space>(
                   devReduced[0])
                   .fetch_add(localReduction[0]);
           });
         }).wait();
      },
      numIters, "Reduction using local and global atomics");

  q.memcpy(&devAns[1], devReduced, sizeof(T)).wait();

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got global atomics device ans " << devAns[0] / numIters << '\n';
  std::cout << "Got global and local atomics device ans "
            << devAns[1] / numIters << '\n';
  std::cout << "vs serial ans " << serialAns << "\n\n";

  sycl::free(devA, q);
  sycl::free(devReduced, q);
}
