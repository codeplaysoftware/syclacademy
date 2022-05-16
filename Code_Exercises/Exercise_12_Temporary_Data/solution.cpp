/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

//#define SYCL_ACADEMY_USING_COMPUTECPP

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

class kernel_a_1;
class kernel_b_1;
class kernel_a_2;
class kernel_b_2;

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

TEST_CASE("buffer_accessor_temporary_data", "temporary_data_solution") {
  constexpr size_t dataSize = 1024;

  float in[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    in[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto gpuQueue = sycl::queue{sycl::gpu_selector{}, asyncHandler};

    auto bufIn = sycl::buffer{in, sycl::range{dataSize}};
    auto bufInt = sycl::buffer<float>{sycl::range{dataSize}};
    auto bufOut = sycl::buffer<float>{sycl::range{dataSize}};

    bufIn.set_final_data(nullptr);
    bufOut.set_final_data(out);

    gpuQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accIn{bufIn, cgh, sycl::read_only};
      sycl::accessor accOut{bufInt, cgh, sycl::write_only};

      cgh.parallel_for<kernel_a_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] = accIn[idx] * 8.0f;
      });
    });

    gpuQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accIn{bufInt, cgh, sycl::read_only};
      sycl::accessor accOut{bufOut, cgh, sycl::write_only};

      cgh.parallel_for<kernel_b_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] = accIn[idx] / 2.0f;
      });
    });

    gpuQueue.wait_and_throw();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 4.0f);
  }
}

TEST_CASE("usm_temporary_data", "temporary_data_solution") {
  constexpr size_t dataSize = 1024;

  float in[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    in[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto usmQueue = sycl::queue{usm_selector{}, asyncHandler};

#ifdef SYCL_ACADEMY_USING_COMPUTECPP
    auto devicePtrIn = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrInt = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrOut = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
#else
    auto devicePtrIn = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrInt = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrOut = sycl::malloc_device<float>(dataSize, usmQueue);
#endif

    auto e1 = usmQueue.memcpy(devicePtrIn, in, sizeof(float) * dataSize);

    auto e2 = usmQueue.parallel_for<kernel_a_2>(
        sycl::range{dataSize}, e1, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrInt[globalId] = devicePtrIn[globalId] * 8.0f;
        });

    auto e3 = usmQueue.parallel_for<kernel_b_2>(
        sycl::range{dataSize}, e2, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrOut[globalId] = devicePtrInt[globalId] / 2.0f;
        });

    usmQueue
        .submit([&](sycl::handler& cgh) {
          cgh.depends_on(e3);
          cgh.memcpy(out, devicePtrOut, sizeof(float) * dataSize);
        })
        .wait();

    sycl::free(devicePtrIn, usmQueue);
    sycl::free(devicePtrInt, usmQueue);
    sycl::free(devicePtrOut, usmQueue);

    usmQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 4.0f);
  }
}
