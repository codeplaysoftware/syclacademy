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

TEST_CASE("buffer_accessor_in_order_queue", "in_order_queue_solution") {
  constexpr size_t dataSize = 1024;

  float inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
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

    auto inOrderQueue = sycl::queue{sycl::gpu_selector{},
                                    asyncHandler,
                                    {sycl::property::queue::in_order{}}};

    auto bufInA = sycl::buffer{inA, sycl::range{dataSize}};
    auto bufInB = sycl::buffer{inB, sycl::range{dataSize}};
    auto bufInC = sycl::buffer{inC, sycl::range{dataSize}};
    auto bufOut = sycl::buffer{out, sycl::range{dataSize}};

    inOrderQueue.submit([&](sycl::handler& cgh) {
      auto acc = bufInA.get_access<sycl::access::mode::read_write>(cgh);

      cgh.parallel_for<kernel_a_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        acc[idx] = acc[idx] * 2.0f;
      });
    });

    inOrderQueue.submit([&](sycl::handler& cgh) {
      auto accIn = bufInA.get_access<sycl::access::mode::read>(cgh);
      auto accOut = bufInB.get_access<sycl::access::mode::write>(cgh);

      cgh.parallel_for<kernel_b_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] += accIn[idx];
      });
    });

    inOrderQueue.submit([&](sycl::handler& cgh) {
      auto accIn = bufInA.get_access<sycl::access::mode::read>(cgh);
      auto accOut = bufInC.get_access<sycl::access::mode::write>(cgh);

      cgh.parallel_for<kernel_c_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] -= accIn[idx];
      });
    });

    inOrderQueue.submit([&](sycl::handler& cgh) {
      auto accInA = bufInB.get_access<sycl::access::mode::read>(cgh);
      auto accInB = bufInC.get_access<sycl::access::mode::read>(cgh);
      auto accOut = bufOut.get_access<sycl::access::mode::write>(cgh);

      cgh.parallel_for<kernel_d_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] = accInA[idx] + accInB[idx];
      });
    });

    inOrderQueue.wait_and_throw();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 2.0f);
  }
}

TEST_CASE("usm_in_order_queue", "in_order_queue_solution") {
  constexpr size_t dataSize = 1024;

  float inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
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

    auto inOrderQueue = sycl::queue{
        usm_selector{}, asyncHandler, {sycl::property::queue::in_order{}}};
    
    auto devicePtrInA = sycl::malloc_device<float>(dataSize, inOrderQueue);
    auto devicePtrInB = sycl::malloc_device<float>(dataSize, inOrderQueue);
    auto devicePtrInC = sycl::malloc_device<float>(dataSize, inOrderQueue);
    auto devicePtrOut = sycl::malloc_device<float>(dataSize, inOrderQueue);

    inOrderQueue.memcpy(devicePtrInA, inA, sizeof(float) * dataSize);
    inOrderQueue.memcpy(devicePtrInB, inB, sizeof(float) * dataSize);
    inOrderQueue.memcpy(devicePtrInC, inC, sizeof(float) * dataSize);
    inOrderQueue.memcpy(devicePtrOut, out, sizeof(float) * dataSize);

    inOrderQueue
        .parallel_for<kernel_a_2>(sycl::range{dataSize},
                                  [=](sycl::id<1> idx) {
                                    auto globalId = idx[0];
                                    devicePtrInA[globalId] =
                                        devicePtrInA[globalId] * 2.0f;
                                  });

    inOrderQueue
        .parallel_for<kernel_b_2>(sycl::range{dataSize},
                                  [=](sycl::id<1> idx) {
                                    auto globalId = idx[0];
                                    devicePtrInB[globalId] +=
                                        devicePtrInA[globalId];
                                  });

    inOrderQueue
        .parallel_for<kernel_c_2>(sycl::range{dataSize},
                                  [=](sycl::id<1> idx) {
                                    auto globalId = idx[0];
                                    devicePtrInC[globalId] -=
                                        devicePtrInA[globalId];
                                  });

    inOrderQueue
        .parallel_for<kernel_d_2>(sycl::range{dataSize},
                                  [=](sycl::id<1> idx) {
                                    auto globalId = idx[0];
                                    devicePtrOut[globalId] =
                                        devicePtrInB[globalId] +
                                        devicePtrInC[globalId];
                                  });

    inOrderQueue.memcpy(inA, devicePtrInA, sizeof(float) * dataSize);
    inOrderQueue.memcpy(inB, devicePtrInB, sizeof(float) * dataSize);
    inOrderQueue.memcpy(inC, devicePtrInC, sizeof(float) * dataSize);
    inOrderQueue.memcpy(out, devicePtrOut, sizeof(float) * dataSize);

    inOrderQueue.wait_and_throw();

    sycl::free(devicePtrInA, inOrderQueue);
    sycl::free(devicePtrInB, inOrderQueue);
    sycl::free(devicePtrInC, inOrderQueue);
    sycl::free(devicePtrOut, inOrderQueue);

  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 2.0f);
  }
}
