/*
 * This code performs a reduce operation over an array.
 *
 * The reduction happens in two steps:
 *
 * 1. Reduce over a workgroup with reduce_over_group
 * 2. Reduce globally using a global atomic_ref
 *
 */

#include <benchmark.h>
#include <sycl/sycl.hpp>

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;
constexpr int numIters = 100;

int main(int argc, char *argv[]) {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devA = sycl::malloc_device<T>(dataSize, q);
  T *devReduced = sycl::malloc_device<T>(1, q); // Holds reduction output

  auto e1 = q.memcpy(devA, a, sizeof(T) * dataSize);
  auto e2 = q.fill(devReduced, 0, 1);

  auto myNd = sycl::nd_range(sycl::range(dataSize), sycl::range(workGroupSize));

  util::benchmark(
      [&]() {
        q.submit([&](sycl::handler &cgh) {
           cgh.depends_on({e1, e2});
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
                 item.get_group(), localMem[localIdx], sycl::plus<T>());

             if (localIdx == 0)
               sycl::atomic_ref<T, sycl::memory_order_relaxed,
                                sycl::memory_scope_device,
                                sycl::access::address_space::global_space>(
                   devReduced[0])
                   .fetch_add(groupReduction);
           });
         }).wait();
      },
      numIters, "Reduction using group algorithms");

  T devAns = 0;
  q.memcpy(&devAns, devReduced, sizeof(T)).wait();

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns / numIters << '\n';
  std::cout << "vs serial ans " << serialAns << "\n\n";

  sycl::free(devA, q);
  sycl::free(devReduced, q);
}
