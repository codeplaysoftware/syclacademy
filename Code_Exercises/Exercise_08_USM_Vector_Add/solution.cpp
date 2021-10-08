/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

class vector_add;

class usm_selector : public sycl::device_selector {
 public:
  int operator()(const sycl::device& dev) const {
    if (dev.has(sycl::aspect::usm_device_allocations)) {
      if (dev.has(sycl::aspect::gpu)) return 2;
      return 1;
    }
    return -1;
  }
};

TEST_CASE("usm_vector_add", "usm_vector_add_solution") {
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

    auto usmQueue = sycl::queue{usm_selector{}, asyncHandler};

#ifdef SYCL_ACADEMY_USE_COMPUTECPP
    auto devicePtrA = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrB = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrR = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
#else
    auto devicePtrA = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrB = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrR = sycl::malloc_device<float>(dataSize, usmQueue);
#endif

    usmQueue.memcpy(devicePtrA, a, sizeof(float) * dataSize).wait();
    usmQueue.memcpy(devicePtrB, b, sizeof(float) * dataSize).wait();

    usmQueue
        .parallel_for<vector_add>(sycl::range{dataSize},
                                  [=](sycl::id<1> idx) {
                                    auto globalId = idx[0];
                                    devicePtrR[globalId] =
                                        devicePtrA[globalId] +
                                        devicePtrB[globalId];
                                  })
        .wait();

    usmQueue.memcpy(r, devicePtrR, sizeof(float) * dataSize).wait();

    sycl::free(devicePtrA, usmQueue);
    sycl::free(devicePtrB, usmQueue);
    sycl::free(devicePtrR, usmQueue);

    usmQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}
