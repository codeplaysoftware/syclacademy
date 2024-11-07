/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

// Runs a simple microbenchmark to compare dispatching a non parallel task to:
//
// 1. An in order queue
//
// TODO: Check how this compares to an out of order queue
//
// This microbenchmark aims to demonstrate that weakly parallel, non dependent
// tasks can benefit from being dispatched concurrently.
//
// Caveat: In general if the programmer has many tasks to dispatch, in SYCL it
// is best to try to encapsulate the logic into as few kernels as possible. The
// work done by `numIters` `single_task`s here would be better encapsulated in
// a single `parallel_for` launch with range `numIters`.

#include <sycl/sycl.hpp>

#include "queue_benchmarking_helpers.hpp"

using T = float;

constexpr int numIters = 100;

// Run busy_sleep numKernels times on a single thread using single_task
template <typename T> auto bench(sycl::queue q, int numKernels) {
  auto *out = sycl::malloc_device<T>(numKernels, q);

  auto s = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < numKernels; i++) {
    q.single_task([=]() { out[i] = busy_sleep<T>(2E5, i); });
  }
  q.wait();
  auto e = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
}

void test_in_order_slow() {
  sycl::queue q{sycl::property::queue::in_order{}};
  bench<T>(q, 1); // Warmup

  auto singleKernelTime = bench<T>(q, 1);
  auto nKernelsTime = bench<T>(q, numIters);
  std::cout << "1 kernel took: " << singleKernelTime << "ms" << std::endl;
  std::cout << numIters << " kernels took: " << nKernelsTime << "ms"
            << std::endl;
  std::cout << "Ratio N/1: "
            << static_cast<float>(nKernelsTime) / singleKernelTime << std::endl
            << std::endl;
}

int main() {
  test_in_order_slow();
}
