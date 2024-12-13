/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 The tiling should work as follows:

 The groupOffset will need to be inverted, as well as the localId.

 In:                                      Out:
 +----------------------------+           +----------------------------+
 |             group  ^       |           |       ^                    |
 |           Offset[1]|       |           |       |                    |
 |                    V       |           |       |                    |
 |<------------------>+-------+           |       |                    |
 |   groupOffset[0]   |1     2|           |       |groupOffset[0]      |
 |                    | tile  |           |       |                    |
 |                    |3     4| ------->  |       |                    |
 |                    +-------+           |       V                    |
 |                            |           |       +-------+            |
 |                            |           |       |1     3|            |
 |                            |           |       | tile  |            |
 |                            |           |       |2     4|            |
 +----------------------------+           +-------+-------+------------+
                                           <----->
                                           groupOffset[1]

Within a tile, each work item is assigned to a single value:

InTile:               OutTile:
+------------+        +------------+
|   local  ^ |        |  local^    |
|   Id[1]  | |        |  Id[0]|    |
|          V |------->|       |    |
|<-------->* |        |       V    |
|localId[0]  |        |<----->*    |
+------------+        +------------+
                      localId[1]

*/

#include <benchmark.h>

#include <iostream>
#include <vector>

#include <sycl/sycl.hpp>

#include "../helpers.hpp"

class naive;
class tiled;

constexpr size_t N = 8192;
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
            q.submit([&](sycl::handler& cgh) {
              sycl::accessor inAcc{inBuf, cgh, sycl::read_only};
              sycl::accessor compAcc{compBuf, cgh, sycl::write_only,
                                     sycl::property::no_init{}};

              cgh.parallel_for<naive>(ndRange, [=](sycl::nd_item<2> item) {
                auto globalId = item.get_global_id();
                sycl::id globalIdTranspose{globalId[1], globalId[0]};
                compAcc[globalIdTranspose] = inAcc[globalId];
              });
            });
            q.wait_and_throw();
          },
          numIters, "Naive matrix transpose");

      util::benchmark(
          [&]() {
            q.submit([&](sycl::handler& cgh) {
              sycl::accessor inAcc{inBuf, cgh, sycl::read_only};
              sycl::accessor outAcc{outBuf, cgh, sycl::write_only,
                                    sycl::property::no_init{}};
              sycl::local_accessor<T, 2> localAcc{localRange, cgh};

              cgh.parallel_for<tiled>(ndRange, [=](sycl::nd_item<2> item) {
                // This kernel assumes that localRange[0] == localRange[1]
                auto globalId = item.get_global_id();
                auto localId = item.get_local_id();
                auto localId_T = sycl::range{localId[1], localId[0]};
                auto groupOffset = globalId - localId;
                auto groupOffset_T =
                    sycl::range{groupOffset[1], groupOffset[0]};

                // Read from global memory in row major and write to local
                // memory in column major
                localAcc[localId_T] = inAcc[globalId];

                // We need to wait here to ensure that all work items have
                // written to local memory before we start reading from it.
                sycl::group_barrier(item.get_group());

                // Read from local memory in row major and write to global
                // memory in row major fashion
                outAcc[groupOffset_T + localId] = localAcc[localId];
              });
            });
            q.wait_and_throw();
          },
          numIters, "Tiled local memory matrix transpose");
    }
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (auto i = 0; i < N * N; ++i) {
    SYCLACADEMY_ASSERT(A_T[i] == A_T_comparison[i]);
  }
}
