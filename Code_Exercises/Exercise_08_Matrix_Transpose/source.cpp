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

#if __has_include(<sycl/sycl.hpp>)
#include <sycl/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

#include <benchmark.h>

constexpr size_t N = 1024;

using T = float;

int main() {

  auto A = std::vector<T>(N * N);
  auto A_T = std::vector<T>(N * N);
  auto A_T_comparison = std::vector<T>(N * N);

  for (auto i = 0; i < N * N; ++i) {
    A[i] = i;
  }

  try {
    auto q = sycl::queue{};

    std::cout << "Running on "
              << q.get_device().get_info<sycl::info::device::name>() << "\n";

    auto globalRange = sycl::range{N, N};
    auto localRange = sycl::range(8, 8);
    auto ndRange = sycl::nd_range(globalRange, localRange);

    {
      auto inBuf = sycl::buffer{A.data(), globalRange};
      auto outBuf = sycl::buffer{A_T.data(), globalRange};
      auto compBuf = sycl::buffer{A_T_comparison.data(), globalRange};

      util::benchmark(
          [&]() {
            q.submit([&](sycl::handler &cgh) {
              auto inAcc = sycl::accessor{inBuf, cgh, sycl::read_only};
              auto compAcc = sycl::accessor{compBuf, cgh, sycl::write_only,
                                            sycl::property::no_init{}};

              cgh.parallel_for(ndRange, [=](sycl::nd_item<2> item) {
                auto globalId = item.get_global_id();
                auto globalIdTranspose = sycl::id{globalId[1], globalId[0]};
                compAcc[globalIdTranspose] = inAcc[globalId];
              });
            });
            q.wait_and_throw();
          },
          100, "Naive matrix transpose");

      util::benchmark(
          [&]() {
            q.submit([&](sycl::handler &cgh) {
              // TODO implement a tiled local memory matrix transpose.
            });
            q.wait_and_throw();
          },
          100, "Tiled local memory matrix transpose");
    }
  } catch (sycl::exception e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (auto i = 0; i < N * N; ++i) {
    assert(A_T[i] == A_T_comparison[i]);
  }
}
