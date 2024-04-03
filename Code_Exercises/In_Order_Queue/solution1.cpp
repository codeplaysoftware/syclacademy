#include <sycl.hpp>

#define MAD_4(x, y)                                                                                \
  x = y * x + y;                                                                                   \
  y = x * y + x;                                                                                   \
  x = y * x + y;                                                                                   \
  y = x * y + x;
#define MAD_16(x, y)                                                                               \
  MAD_4(x, y);                                                                                     \
  MAD_4(x, y);                                                                                     \
  MAD_4(x, y);                                                                                     \
  MAD_4(x, y);
#define MAD_64(x, y)                                                                               \
  MAD_16(x, y);                                                                                    \
  MAD_16(x, y);                                                                                    \
  MAD_16(x, y);                                                                                    \
  MAD_16(x, y);

template <class T> static T busy_sleep(size_t N, T i) {
  T x = 1.3f;
  T y = i;
  for (size_t j = 0; j < N; j++) {
    MAD_64(x, y);
  }
  return y;
}

auto bench(sycl::queue Q, int N_kernel) {
  auto *out = sycl::malloc_device<double>(N_kernel, Q);

  const auto s = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N_kernel; i++) {
    Q.single_task([=]() { out[i] = busy_sleep<float>(2E5, i); });
  }
  Q.wait();
  const auto e = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
}

auto bench_multiple_queues(std::vector<sycl::queue> Qs, int N_kernel_per_queue) {

  auto *out = sycl::malloc_device<double>(N_kernel_per_queue * Qs.size(), Qs[0]);

  const auto s = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N_kernel_per_queue; i++) {
    for (auto Q : Qs) {
      Q.single_task([=]() { out[i] = busy_wait<double>(1E5, i); });
    }
  }
  for (auto Q : Qs) {
    Q.wait();
  }
  const auto e = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
}

TEST_CASE("in_order_queue", "in_order_slow") {
 sycl::queue Q{sycl::property::queue::in_order{}};
 bench(Q, 1); // Warmup

 const int N = 100;
 auto kernels_1 =  bench(Q, 1);
 std::cout << "1" << " kernels took: " << kernels_1 << "ms" << std::endl;
 auto kernels_N =  bench(Q, N);
 std::cout << N << " kernels took: " <<kernels_N << "ms" << std::endl;
 std::cout << "Ratio N/1: " << kernels_N / kernels_1 << std::endl;
}

TEST_CASE("in_order_queue", "out_of_order") {
 sycl::queue Q;
 bench(Q, 1); // Warmup

 const int N = 100;
 auto kernels_1 =  bench(Q, 1);
 std::cout << "1" << " kernels took: " << kernels_1 << "ms" << std::endl;
 auto kernels_N =  bench(Q, N);
 std::cout << N << " kernels took: " <<kernels_N << "ms" << std::endl;
 std::cout << "Ratio N/1: " << kernels_N / kernels_1 << std::endl;
}


TEST_CASE("in_order_queue", "in_order_fast") {

 const int N_kernel_per_queue = 10;
 const int N_queues = 10;

 std::vector<sycl::queue> Qs;
 for (int i=0; i<N_queues; i++) {
   sycl::queue Q{sycl::property::queue::in_order{}};
   Qs.push_back(Q);
 }
 bench_multiple_queues({Q[0]},1); // Trigger JITing
 
 auto kernels_1 =  bench_multiple_queues({Q[0]},1);
 std::cout << "1" << " kernels took: " << kernels_1 << "ms" << std::endl;

 auto kernels_N =  bench_multiple_queues(Qs, N_queues);
 std::cout << N << " in-order_fast kernels took: " <<kernels_N << "ms" << std::endl;
 std::cout << "Ratio N/1: " << kernels_N / kernels_1 << std::endl;
}

