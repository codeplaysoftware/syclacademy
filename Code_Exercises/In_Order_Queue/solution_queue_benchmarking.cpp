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
// 2. An out of order queue
// 3. Multiple in order queues
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

// Run busy_sleep numKernels times on multiple in order queues using
// single_task
template <typename T>
auto bench_multiple_queues(std::vector<sycl::queue> qs,
                           int numKernelsPerQueue) {

  auto *out = sycl::malloc_device<T>(numKernelsPerQueue * qs.size(), qs[0]);

  auto s = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < numKernelsPerQueue; i++) {
    for (auto q : qs) {
      q.single_task([=]() { out[i] = busy_sleep<T>(1E5, i); });
    }
  }
  for (auto q : qs) {
    q.wait();
  }
  auto e = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
}

void run_single_queue(sycl::queue q) {
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

void test_in_order_slow() {
  sycl::queue q{sycl::property::queue::in_order{}};
  run_single_queue(q);
}

void test_out_of_order() {
  sycl::queue q;
  run_single_queue(q);
}

void test_multiple_in_order_queues() {

  constexpr int numKernelsPerQueue = 10;
  constexpr int numQueues = numIters / numKernelsPerQueue;

  std::vector<sycl::queue> qs;
  for (int i = 0; i < numQueues; i++) {
    sycl::queue q{sycl::property::queue::in_order{}};
    qs.push_back(q);
  }
  bench_multiple_queues<T>({qs[0]}, 1); // Warmup

  auto singleKernelTime = bench<T>({qs[0]}, 1);
  auto nKernelsTime = bench_multiple_queues<T>(qs, numQueues);
  std::cout << "1 kernel took: " << singleKernelTime << "ms" << std::endl;
  std::cout << numIters << " in-order kernels took: " << nKernelsTime << "ms"
            << std::endl;
  std::cout << "Ratio N/1: "
            << static_cast<float>(nKernelsTime) / singleKernelTime << std::endl
            << std::endl;
}

int main() {
  test_in_order_slow();
  test_out_of_order();
  test_multiple_in_order_queues();
}
