/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 SYCL Quick Reference
 ~~~~~~~~~~~~~~~~~~~~

 // Declare a local accessor
 sycl::accessor<T, dims,
          sycl::access:mode::read_write, sycl::access::target_local>
                local_acc{localRange, cgh};
*/

#include <iostream>
#include <vector>

#include <sycl/sycl.hpp>

#include <benchmark.h>

constexpr size_t N = 1024;
constexpr size_t numIters = 100;

using T = float;

int main() {

  std::vector<T> A(N * N);
  std::vector<T> A_T(N * N);
  std::vector<T> A_T_comparison(N * N);

  for (auto i = 0; i < N * N; ++i) {
    A[i] = i;
  }

  try {
    auto q = sycl::queue{};

    std::cout << "Running on "
              << q.get_device().get_info<sycl::info::device::name>() << "\n";

    sycl::range globalRange{N, N};
    sycl::range localRange{16, 16};
    sycl::nd_range ndRange{globalRange, localRange};

    {
      sycl::buffer inBuf{A.data(), globalRange};
      sycl::buffer outBuf{A_T.data(), globalRange};
      sycl::buffer compBuf{A_T_comparison.data(), globalRange};

      util::benchmark(
          [&]() {
            q.submit([&](sycl::handler &cgh) {
              sycl::accessor inAcc{inBuf, cgh, sycl::read_only};
              sycl::accessor compAcc{compBuf, cgh, sycl::write_only,
                                     sycl::property::no_init{}};

              cgh.parallel_for(ndRange, [=](sycl::nd_item<2> item) {
                auto globalId = item.get_global_id();
                auto globalIdTranspose = sycl::id{globalId[1], globalId[0]};
                compAcc[globalIdTranspose] = inAcc[globalId];
              });
            });
            q.wait_and_throw();
          },
          numIters, "Naive matrix transpose");

      util::benchmark(
          [&]() {
            q.submit([&](sycl::handler &cgh) {
              // TODO implement a tiled local memory matrix transpose.
            });
            q.wait_and_throw();
          },
          numIters, "Tiled local memory matrix transpose");
    }
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (auto i = 0; i < N * N; ++i) {
    assert(A_T[i] == A_T_comparison[i]);
  }
}
