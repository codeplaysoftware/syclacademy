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

class kernel_a_1;
class kernel_b_1;
class kernel_c_1;
class kernel_d_1;
class kernel_a_2;
class kernel_b_2;
class kernel_c_2;
class kernel_d_2;

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

TEST_CASE("buffer_accessor_diamond", "managing_dependencies_solution") {
  constexpr size_t dataSize = 1024;

  int inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = static_cast<float>(i);
    inB[i] = static_cast<float>(i);
    inC[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto defaultQueue = sycl::queue{sycl::default_selector{}, asyncHandler};

    auto bufInA = sycl::buffer{inA, sycl::range{dataSize}};
    auto bufInB = sycl::buffer{inB, sycl::range{dataSize}};
    auto bufInC = sycl::buffer{inC, sycl::range{dataSize}};
    auto bufOut = sycl::buffer{out, sycl::range{dataSize}};

    defaultQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor acc{bufInA, cgh, sycl::read_write};

      cgh.parallel_for<kernel_a_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        acc[idx] = acc[idx] * 2.0f;
      });
    });

    defaultQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accIn{bufInA, cgh, sycl::read_only};
      sycl::accessor accOut{bufInB, cgh, sycl::write_only};

      cgh.parallel_for<kernel_b_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] += accIn[idx];
      });
    });

    defaultQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accIn{bufInA, cgh, sycl::read_only};
      sycl::accessor accOut{bufInC, cgh, sycl::write_only};

      cgh.parallel_for<kernel_c_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] -= accIn[idx];
      });
    });

    defaultQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accInA{bufInB, cgh, sycl::read_only};
      sycl::accessor accInB{bufInC, cgh, sycl::read_only};
      sycl::accessor accOut{bufOut, cgh, sycl::write_only};

      cgh.parallel_for<kernel_d_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] = accInA[idx] + accInB[idx];
      });
    });

    defaultQueue.wait_and_throw();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 2.0f);
  }
}

TEST_CASE("usm_diamond", "usm_vector_add_solution") {
  constexpr size_t dataSize = 1024;

  int inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = static_cast<float>(i);
    inB[i] = static_cast<float>(i);
    inC[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto usmQueue = sycl::queue{usm_selector{}, asyncHandler};

#ifdef SYCL_ACADEMY_USE_COMPUTECPP
    auto devicePtrInA = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrInB = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrInC = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrOut = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
#else
    auto devicePtrInA = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrInB = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrInC = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrOut = sycl::malloc_device<float>(dataSize, usmQueue);
#endif

    auto e1 = usmQueue.memcpy(devicePtrInA, inA, sizeof(float) * dataSize);
    auto e2 = usmQueue.memcpy(devicePtrInB, inB, sizeof(float) * dataSize);
    auto e3 = usmQueue.memcpy(devicePtrInC, inC, sizeof(float) * dataSize);

    auto e4 = usmQueue.parallel_for<kernel_a_2>(
        sycl::range{dataSize}, {e1, e2, e3}, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrInA[globalId] = devicePtrInA[globalId] * 2.0f;
        });

    auto e5 = usmQueue.parallel_for<kernel_b_2>(
        sycl::range{dataSize}, e4, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrInB[globalId] += devicePtrInA[globalId];
        });

    auto e6 = usmQueue.parallel_for<kernel_c_2>(
        sycl::range{dataSize}, e4, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrInC[globalId] -= devicePtrInA[globalId];
        });

    auto e7 = usmQueue.parallel_for<kernel_d_2>(
        sycl::range{dataSize}, {e5, e6}, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrOut[globalId] =
              devicePtrInB[globalId] + devicePtrInC[globalId];
        });

    auto e8 = usmQueue.memcpy(out, devicePtrOut, sizeof(float) * dataSize, e7);

    e8.wait();

    sycl::free(devicePtrInA, usmQueue);
    sycl::free(devicePtrInB, usmQueue);
    sycl::free(devicePtrInC, usmQueue);
    sycl::free(devicePtrOut, usmQueue);

    usmQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 2.0f);
  }
}
