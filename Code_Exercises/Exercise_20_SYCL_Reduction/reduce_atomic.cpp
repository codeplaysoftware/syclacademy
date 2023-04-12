/*
 * This code performs a reduce operation over an array.
 *
 * The reduction happens in two steps:
 *
 * 1. Reduce over a workgroup with a local memory atomic
 * 2. Reduce globally using a global atomic_ref
 *
 */

#include <sycl/sycl.hpp>

template <typename T> constexpr T my_min(T a, T b) { return a < b ? a : b; }

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;
constexpr size_t numWorkGroups =
    my_min(workGroupSize, dataSize / workGroupSize);

int main(int argc, char *argv[]) {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devA = sycl::malloc_device<T>(dataSize, q);
  T *devReduced = sycl::malloc_device<T>(1, q); // Holds intermediate values

  T zeroVal = 0;
  auto e1 = q.memcpy(devA, a, sizeof(T) * dataSize);
  auto e2 = q.memcpy(devReduced, &zeroVal, sizeof(T));

  auto myNd = sycl::nd_range(sycl::range(numWorkGroups * workGroupSize),
                             sycl::range(workGroupSize));

  auto e3 = q.submit([&](sycl::handler &cgh) {
    cgh.depends_on({e1, e2});
    sycl::local_accessor<T, 1> localMem(workGroupSize, cgh);
    sycl::local_accessor<T, 1> localReduction(1, cgh);

    cgh.parallel_for(myNd, [=](sycl::nd_item<1> item) {
      auto localIdx = item.get_local_linear_id();
      auto globalIdx = item.get_global_linear_id();
      auto globalRange = item.get_global_range(0);

      localMem[localIdx] = 0;

      // Accumulating thread local reductions into local memory
      for (auto i = globalIdx; i < dataSize; i += globalRange) {
        localMem[localIdx] += devA[i];
      }

      localReduction[0] = 0;
      item.barrier();

      // Work group atomic add into local mem
      sycl::atomic_ref<T, sycl::memory_order_relaxed,
                       sycl::memory_scope_work_group,
                       sycl::access::address_space::local_space>(
          localReduction[0])
          .fetch_add(localMem[localIdx]);

      item.barrier();

      if (localIdx == 0)
        sycl::atomic_ref<T, sycl::memory_order_relaxed,
                         sycl::memory_scope_work_group,
                         sycl::access::address_space::global_space>(
            devReduced[0])
            .fetch_add(localReduction[0]);
    });
  });

  T devAns = 0;
  q.memcpy(&devAns, devReduced, sizeof(T), e3).wait();

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << '\n';

  sycl::free(devA, q);
  sycl::free(devReduced, q);
}
