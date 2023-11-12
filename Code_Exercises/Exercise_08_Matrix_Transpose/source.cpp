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

/* Visualization
 
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

      // Task: Transpose a matrix using local memory
      util::benchmark(
          [&]() {
            q.submit([&](sycl::handler &cgh) {
              auto inAcc = sycl::accessor{inBuf, cgh, sycl::read_only};
              auto outAcc = sycl::accessor{outBuf, cgh, sycl::write_only,
                                            sycl::property::no_init{}};
              // TODO 1: Allocate local memory for the kernel function by 
              // creating an 2-dimentional `local_accessor` with the size equal
              // to the `localRange`

              cgh.parallel_for(ndRange, [=](sycl::nd_item<2> item) {
                auto globalId = item.get_global_id();
                auto globalIdTranspose = sycl::id{globalId[1], globalId[0]};
                // TODO 2a: Get the with-in-a-work-group thread id with 
                // `get_local_id()` member function

                // TODO 2b: Calculate group index offset (bw globalId and localId)
                
                // TODO 2c: Get `localIdTranspose` and `groupOffsetTranspose`

                // TODO 2d: Read from global memory in row major and write to local
                // memory in column major (using `localIdTranspose` and `globalId`)
                
                // TODO 2e: Synchronize the work-group via a `barrier` to avoid data race

                // TODO 2f: Read from local memory in row major and write to global
                // memory in row major fashion (using `localId` and `groupOffsetTranspose`)
                outAcc[globalIdTranspose] = inAcc[globalId];

                });
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
