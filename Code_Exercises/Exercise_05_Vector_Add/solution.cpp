/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <sycl/sycl.hpp>

class vector_add;
class vector_add_usm;

TEST_CASE("vector_add", "vector_add_solution") {
  constexpr size_t dataSize = 1024;

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

    auto defaultQueue = sycl::queue{sycl::default_selector_v, asyncHandler};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    defaultQueue
        .submit([&](sycl::handler& cgh) {
          sycl::accessor accA{bufA, cgh, sycl::read_only};
          sycl::accessor accB{bufB, cgh, sycl::read_only};
          sycl::accessor accR{bufR, cgh, sycl::write_only};

          cgh.parallel_for<vector_add>(
              sycl::range{dataSize},
              [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
        })
        .wait();

    defaultQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}

TEST_CASE("vector_add_usm", "vector_add_solution") {
  constexpr size_t dataSize = 1024;

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

    auto defaultQueue = sycl::queue{sycl::default_selector_v, asyncHandler};

    auto devA = sycl::malloc_device<float>(dataSize, defaultQueue);
    auto devB = sycl::malloc_device<float>(dataSize, defaultQueue);
    auto devR = sycl::malloc_device<float>(dataSize, defaultQueue);

    defaultQueue.memcpy(devA, a, sizeof(float) * dataSize);
    defaultQueue.memcpy(devB, b, sizeof(float) * dataSize);

    defaultQueue.wait();

    defaultQueue
        .submit([&](sycl::handler &cgh) {
          cgh.parallel_for<vector_add_usm>(
              sycl::range{dataSize}, [=](sycl::id<1> i) {
                size_t id = i.get(0);
                devR[id] = devA[id] + devB[id];
              });
        })
        .wait();

    defaultQueue.memcpy(r, devR, sizeof(float) * dataSize);

    defaultQueue.wait_and_throw();

    sycl::free(devA, defaultQueue);
    sycl::free(devB, defaultQueue);
    sycl::free(devR, defaultQueue);
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}
