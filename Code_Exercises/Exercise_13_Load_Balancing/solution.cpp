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

class vector_add_first;
class vector_add_second;

TEST_CASE("load_balancing", "load_balancing_solution") {
  constexpr size_t dataSize = 1024;
  constexpr float ratio = 0.5f;
  constexpr size_t dataSizeFirst = ratio * dataSize;
  constexpr size_t dataSizeSecond = (1 - ratio) * dataSize;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto cpuDevice = sycl::cpu_selector_v.select_device();
    auto gpuDevice = sycl::gpu_selector_v.select_device();

    auto jointContext = sycl::context({cpuDevice, gpuDevice});

    auto cpuQueue = sycl::queue{jointContext, cpuDevice, asyncHandler};
    auto gpuQueue = sycl::queue{jointContext, gpuDevice, asyncHandler};

    auto bufFirstA = sycl::buffer{a, sycl::range{dataSizeFirst}};
    auto bufFirstB = sycl::buffer{b, sycl::range{dataSizeFirst}};
    auto bufFirstR = sycl::buffer{r, sycl::range{dataSizeFirst}};

    auto bufSecondA =
        sycl::buffer{a + dataSizeFirst, sycl::range{dataSizeSecond}};
    auto bufSecondB =
        sycl::buffer{b + dataSizeFirst, sycl::range{dataSizeSecond}};
    auto bufSecondR =
        sycl::buffer{r + dataSizeFirst, sycl::range{dataSizeSecond}};

    gpuQueue.submit([&](sycl::handler& cgh) {
      auto accA = bufFirstA.get_access<sycl::access::mode::read>(cgh);
      auto accB = bufFirstB.get_access<sycl::access::mode::read>(cgh);
      auto accR = bufFirstR.get_access<sycl::access::mode::write>(cgh);

      cgh.parallel_for<vector_add_first>(
          sycl::range{dataSize},
          [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
    });

    gpuQueue.submit([&](sycl::handler& cgh) {
      auto accA = bufSecondA.get_access<sycl::access::mode::read>(cgh);
      auto accB = bufSecondB.get_access<sycl::access::mode::read>(cgh);
      auto accR = bufSecondR.get_access<sycl::access::mode::write>(cgh);

      cgh.parallel_for<vector_add_second>(
          sycl::range{dataSize},
          [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
    });

    cpuQueue.wait_and_throw();
    gpuQueue.wait_and_throw();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}
