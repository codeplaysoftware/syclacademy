/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 SYCL Quick Reference
 ~~~~~~~~~~~~~~~~~~~~

 // oneMKL APIs:
 https://spec.oneapi.io/versions/latest/elements/oneMKL/source/domains/blas/gemm.html#onemkl-blas-gemm

 // DGEMM:
 https://www.intel.com/content/www/us/en/docs/onemkl/tutorial-c/2021-4/multiplying-matrices-using-dgemm.html

*/

#include <iostream>
#include <limits>
#include <random>

#include <oneapi/mkl/blas.hpp>
#include <sycl/sycl.hpp>

// Matrix size constants
constexpr size_t SIZE = 4800; // Must be a multiple of 8.
constexpr size_t M = SIZE / 8;
constexpr size_t N = SIZE / 4;
constexpr size_t P = SIZE / 2;

using T = double;

//////////////////////////////////////////////////////////////////////////////////////////

bool ValueSame(T a, T b) { return std::fabs(a - b) < 1.0e-08; }
int VerifyResult(sycl::host_accessor<T, 1>& c_A, T* c_B) {
  bool MismatchFound = false;

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < P; j++) {
      if (!ValueSame(c_A[i * P + j], c_B[i * P + j])) {
        std::cout << "fail - The result is incorrect for element: [" << i
                  << ", " << j << "], expected: " << c_A[i * P + j]
                  << " , but got: " << c_B[i * P + j] << std::endl;
        MismatchFound = true;
      }
    }
  }

  if (!MismatchFound) {
    std::cout << "SUCCESS - The results are correct!" << std::endl;
    return 0;
  } else {
    std::cout << "FAIL - The results mis-match!" << std::endl;
    return -1;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void print_device_info(sycl::queue& Q) {
  std::string sycl_dev_name, sycl_runtime, sycl_driver;
  sycl_dev_name = Q.get_device().get_info<sycl::info::device::name>();
  sycl_driver = Q.get_device().get_info<sycl::info::device::driver_version>();
  sycl_runtime = Q.get_device().get_info<sycl::info::device::version>();
  std::cout << "Running on " << sycl_dev_name.c_str() << ", SYCL runtime: v"
            << sycl_runtime.c_str()
            << ", driver version: " << sycl_driver.c_str() << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main() {
  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(1.0, 2.0);

  // matrix data sizes
  int m = M;
  int n = P;
  int k = N;

  // leading dimensions of data
  int ldA = k;
  int ldB = n;
  int ldC = n;

  // set scalar fp values
  T alpha = 1.0;
  T beta = 0.0;

  // Allocate memory on host
  std::vector<T> A(M * N);
  std::vector<T> B(N * P);
  std::vector<T> C_host(M * P);

  std::cout << "Problem size: c(" << M << "," << P << ") = a(" << M << "," << N
            << ") * b(" << N << "," << P << ")" << std::endl;

  // A(M, N)
  for (size_t i = 0; i < M; i++)
    for (size_t j = 0; j < N; j++)
      A[i * N + j] = dis(gen);
  // B(N, P)
  for (size_t i = 0; i < N; i++)
    for (size_t j = 0; j < P; j++)
      B[i * P + j] = dis(gen);

  // Resultant matrix: C_serial = A*B
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < P; j++) {
      for (size_t d = 0; d < N; d++) {
        C_host[i * P + j] += A[i * N + d] * B[d * P + j];
      }
    }
  }

  // Create a SYCL in-order queue targetting GPU device
  sycl::queue Q { sycl::gpu_selector_v, sycl::property::queue::in_order {} };
  // Prints some basic info related to the hardware
  print_device_info(Q);

  // TODO: Allocate memory on device, (using sycl::malloc_device APIs)
  // Creating 1D buffers for matrices which are bound to host memory array
  sycl::buffer<T, 1> a { A.data(), sycl::range<1> { M * N } };
  sycl::buffer<T, 1> b { B.data(), sycl::range<1> { N * P } };
  sycl::buffer<T, 1> c { C_host.data(), sycl::range<1> { M * P } };

  // TODO: Use oneMKL GEMM USM API
  oneapi::mkl::transpose transA = oneapi::mkl::transpose::nontrans;
  oneapi::mkl::transpose transB = oneapi::mkl::transpose::nontrans;
  oneapi::mkl::blas::column_major::gemm(Q, transA, transB, n, m, k, alpha, b,
                                        ldB, a, ldA, beta, c, ldC);
  Q.wait();
  sycl::host_accessor C_device { c };

  // Verify results from oneMKL APIs
  int result = 0;
  std::cout << "Verify results between OneMKL & Serial: ";
  result = VerifyResult(C_device, C_host.data());

  return result;
}
