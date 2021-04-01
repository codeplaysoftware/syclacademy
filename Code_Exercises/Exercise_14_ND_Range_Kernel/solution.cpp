/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <SYCL/sycl.hpp>

class vector_add_1;
class vector_add_2;

TEST_CASE("range_kernel_with_item", "nd_range_kernel_solution") {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto gpuQueue = sycl::queue{sycl::gpu_selector_v, asyncHandler};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    gpuQueue.submit([&](sycl::handler& cgh) {
      auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
      auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
      auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

      cgh.parallel_for<vector_add_1>(
          sycl::range{dataSize}, [=](sycl::item<1> itm) {
            auto globalId = itm.get_id();
            accR[globalId] = accA[globalId] + accB[globalId];
          });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}

TEST_CASE("nd_range_kernel", "nd_range_kernel_solution") {
  constexpr size_t dataSize = 1024;
  constexpr size_t workGroupSize = 128;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto gpuQueue = sycl::queue{sycl::gpu_selector_v, asyncHandler};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    gpuQueue.submit([&](sycl::handler& cgh) {
      auto accA = bufA.get_access<sycl::access::mode::read_write>(cgh);
      auto accB = bufB.get_access<sycl::access::mode::read_write>(cgh);
      auto accR = bufR.get_access<sycl::access::mode::read_write>(cgh);

      auto ndRange =
          sycl::nd_range{sycl::range{dataSize}, sycl::range{workGroupSize}};

      cgh.parallel_for<vector_add_2>(ndRange, [=](sycl::nd_item<1> itm) {
        auto globalId = itm.get_global_id();
        accR[globalId] = accA[globalId] + accB[globalId];
      });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}
