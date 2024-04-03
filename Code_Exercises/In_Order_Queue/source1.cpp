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

template <class T> static T busy_wait(size_t N, T i) {
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
    Q.single_task([=]() { out[i] = busy_wait<double>(1E5, i); });
  }
  Q.wait();
  const auto e = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
}

TEST_CASE("in_order_queue", "in_order_slow") {
 sycl::queue Q{sycl::property::queue::in_order{}};
 bench(Q, 1); // Trigger JITing

 const int N = 100;
 auto kernels_1 =  bench(Q, 1);
 std::cout << "1" << " kernels took: " << kernels_1 << "ms" << std::endl;
 auto kernels_N =  bench(Q, N);
 std::cout << N << " kernels took: " <<kernels_N << "ms" << std::endl;
 std::cout << "Ratio N/1: " << kernels_N / kernels_1 << std::endl;
}
