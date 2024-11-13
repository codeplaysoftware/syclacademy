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
 */

#include <benchmark.h>
#include <sycl/sycl.hpp>

template <typename T> constexpr T my_min(T a, T b) { return a < b ? a : b; }

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;
constexpr size_t numWorkGroups =
    my_min(workGroupSize, dataSize / workGroupSize);
constexpr int numIters = 100;

// A device function that reduces an array in local memory into a single value
// at a[0].
template <typename T, size_t workGroupSize>
inline void workgroup_reduce_local_mem(sycl::local_accessor<T, 1> a,
                                       sycl::nd_item<1> &item,
                                       size_t localIdx) {
#pragma unroll
  for (auto i = workGroupSize; i >= 2; i /= 2) {
    if (workGroupSize >= i) {
      if (localIdx < i / 2)
        a[localIdx] += a[localIdx + i / 2];
      item.barrier();
    }
  }
}

int main(int argc, char *argv[]) {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devPtrA = sycl::malloc_device<T>(dataSize, q);
  T *devPtrB =
      sycl::malloc_device<T>(numWorkGroups, q); // Holds intermediate values

  auto e1 = q.memcpy(devPtrA, a, sizeof(T) * dataSize);

  auto myNd = sycl::nd_range(sycl::range(numWorkGroups * workGroupSize),
                             sycl::range(workGroupSize));

  util::benchmark(
      [&]() {
        auto e2 = q.submit([&](sycl::handler &cgh) {
          cgh.depends_on(e1);
          sycl::local_accessor<T, 1> local_mem(workGroupSize, cgh);

          cgh.parallel_for<class step1_reduce>(
              myNd, [=](sycl::nd_item<1> item) {
                auto localIdx = item.get_local_linear_id();
                auto globalIdx = item.get_global_linear_id();
                auto globalRange = item.get_global_range(0);

                local_mem[localIdx] = 0;

                auto arrayIdx = globalIdx;

                // Accumulating thread local reductions into local memory
                while (arrayIdx < dataSize) {
                  local_mem[localIdx] += devPtrA[arrayIdx];
                  arrayIdx += globalRange;
                }
                item.barrier();
                workgroup_reduce_local_mem<T, workGroupSize>(local_mem, item,
                                                             localIdx);
                devPtrB[item.get_group_linear_id()] = local_mem[0];
              });
        });

        q.submit([&](sycl::handler &cgh) {
           cgh.depends_on(e2);
           sycl::local_accessor<T, 1> local_mem(workGroupSize, cgh);

           // Second kernel executed by a single work group
           auto second_nd = sycl::nd_range(sycl::range(workGroupSize),
                                           sycl::range(workGroupSize));

           // Reduce smaller array into a single value
           cgh.parallel_for<class step2_reduce>(
               second_nd, [=](sycl::nd_item<1> item) {
                 auto localIdx = item.get_local_linear_id();
                 local_mem[localIdx] = 0;

                 auto arrayIdx = localIdx;
                 // Accumulating thread local reductions into local memory
                 while (arrayIdx < numWorkGroups) {
                   local_mem[localIdx] += devPtrB[arrayIdx];
                   arrayIdx += workGroupSize;
                 }
                 item.barrier();
                 workgroup_reduce_local_mem<T, workGroupSize>(local_mem, item,
                                                              localIdx);
                 devPtrB[0] = local_mem[0];
               });
         }).wait();
      },
      numIters, "Naive reduction using two kernels");

  T devAns = 0;
  q.memcpy(&devAns, devPtrB, sizeof(T)).wait();

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << "\n\n";

  sycl::free(devPtrA, q);
  sycl::free(devPtrB, q);
}
