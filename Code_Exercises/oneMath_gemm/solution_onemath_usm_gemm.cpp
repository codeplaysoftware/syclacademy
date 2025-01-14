/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 Quick Reference
 ~~~~~~~~~~~~~~~~~~~~

 oneMath execution model:
 https://oneapi-spec.uxlfoundation.org/specifications/oneapi/latest/elements/onemath/source/architecture/architecture

 oneMath GEMM API:
 https://oneapi-spec.uxlfoundation.org/specifications/oneapi/latest/elements/onemath/source/domains/blas/gemm

*/

#include <iostream>
#include <limits>
#include <oneapi/math.hpp>
#include <random>

#include <sycl/sycl.hpp>

// Matrix size constants
constexpr size_t SIZE = 4800;  // Must be a multiple of 8.
constexpr size_t M = SIZE / 8;
constexpr size_t N = SIZE / 4;
constexpr size_t P = SIZE / 2;

using T = double;

//////////////////////////////////////////////////////////////////////////////////////////

bool ValueSame(T a, T b) { return std::fabs(a - b) < 1.0e-08; }
int VerifyResult(T* c_A, T* c_B) {
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
  std::string sycl_dev_name, sycl_dev_version, sycl_driver;
  sycl_dev_name = Q.get_device().get_info<sycl::info::device::name>();
  sycl_driver = Q.get_device().get_info<sycl::info::device::driver_version>();
  sycl_dev_version = Q.get_device().get_info<sycl::info::device::version>();
  std::cout << "Running on " << sycl_dev_name.c_str()
            << ", version: " << sycl_dev_version.c_str()
            << ", driver version: " << sycl_driver.c_str() << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main() {
  std::random_device
      rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
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
    for (size_t j = 0; j < N; j++) A[i * N + j] = dis(gen);
  // B(N, P)
  for (size_t i = 0; i < N; i++)
    for (size_t j = 0; j < P; j++) B[i * P + j] = dis(gen);

  // Resultant matrix: C_serial = A*B
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < P; j++) {
      for (size_t d = 0; d < N; d++) {
        C_host[i * P + j] += A[i * N + d] * B[d * P + j];
      }
    }
  }

  // Create a SYCL queue
  sycl::queue Q;
  // Prints some basic info related to the hardware
  print_device_info(Q);

  // Allocate memory on device, (using sycl::malloc_device APIs)
  T* a = sycl::malloc_device<T>((M * N), Q);
  T* b = sycl::malloc_device<T>((N * P), Q);
  T* c = sycl::malloc_device<T>((M * P), Q);
  sycl::event eventCopyA = Q.memcpy(a, A.data(), sizeof(T) * M * N);
  sycl::event eventCopyB = Q.memcpy(b, B.data(), sizeof(T) * N * P);

  // Use oneMath GEMM USM API
  oneapi::math::transpose transA = oneapi::math::transpose::nontrans;
  oneapi::math::transpose transB = oneapi::math::transpose::nontrans;
  // Pass the synchronisation events to ensure GEMM starts after inputs are
  // fully copied to the device
  sycl::event eventGEMM = oneapi::math::blas::column_major::gemm(
      Q, transA, transB, n, m, k, alpha, b, ldB, a, ldA, beta, c, ldC,
      {eventCopyA, eventCopyB});  // row-major

  // Copy the results from device to host for verification
  std::vector<T> C_device(M * P);
  // Pass the synchronisation event for the copy to wait until GEMM is finished
  sycl::event eventCopyC =
      Q.memcpy(C_device.data(), c, sizeof(T) * M * P, eventGEMM);

  // Wait for the copy to finish
  eventCopyC.wait();

  // Verify results from oneMath
  int result = 0;
  std::cout << "Verify results between oneMath & serial: ";
  result = VerifyResult(C_device.data(), C_host.data());

  // Free memory from device
  sycl::free(a, Q);
  sycl::free(b, Q);
  sycl::free(c, Q);

  return result;
}
