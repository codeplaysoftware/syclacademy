/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#include <CL/sycl.hpp>
#else
#include <SYCL/sycl.hpp>
#endif

class vector_add;

class usm_selector : public sycl::device_selector {
 public:
  int operator()(const sycl::device& dev) const {
    if (dev.has(sycl::aspect::usm_device_allocations)) {
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

    // Write code to allocate the memory you are using with USM
    // E.g. auto devicePtrA = sycl::malloc_device<float>(dataSize, usmQueue);

    // Now write code to copy the memory of the variables being added below 
    // to the device using USM memcpy
    // E.g. usmQueue.memcpy(devicePtrA, a, sizeof(float) * dataSize).wait();

    // Here is the kernel code
    usmQueue
        .parallel_for<vector_add>(sycl::range{dataSize},
                                  [=](sycl::id<1> idx) {
                                    auto globalId = idx[0];
                                    devicePtrR[globalId] =
                                        devicePtrA[globalId] +
                                        devicePtrB[globalId];
                                  })
        .wait();

    // Now write code to copy the result back to your result variable

    // Now write code to free the memory you were using
    // E.g. sycl::free(devicePtrA, usmQueue);

    // Here is some code to catch any asynchronous exceptions
    usmQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}
