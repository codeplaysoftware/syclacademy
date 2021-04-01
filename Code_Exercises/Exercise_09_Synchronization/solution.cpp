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
class vector_add_3;
class vector_add_4;
class vector_add_5;
class vector_add_6;

class usm_selector : public sycl::device_selector {
 public:
  int operator()(const sycl::device& dev) const {
    if (dev.get_info<sycl::info::device::usm_device_allocations>()) {
      return 1;
    }
    return -1;
  }
};

TEST_CASE("buffer_accessor_event_wait", "synchronization_solution") {
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

    gpuQueue
        .submit([&](sycl::handler& cgh) {
          auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
          auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
          auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

          cgh.parallel_for<vector_add_1>(
              sycl::range{dataSize},
              [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
        })
        .wait();  // Synchronize

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {  // Copy back
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}

TEST_CASE("buffer_accessor_queue_wait", "synchronization_solution") {
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

      cgh.parallel_for<vector_add_2>(
          sycl::range{dataSize},
          [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
    });

    gpuQueue.wait_and_throw();          // Synchronize
  } catch (const sycl::exception& e) {  // Copy back
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}

TEST_CASE("buffer_accessor_buffer_dest", "synchronization_solution") {
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

    {
      auto bufA = sycl::buffer{a, sycl::range{dataSize}};
      auto bufB = sycl::buffer{b, sycl::range{dataSize}};
      auto bufR = sycl::buffer{r, sycl::range{dataSize}};

      gpuQueue.submit([&](sycl::handler& cgh) {
        auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
        auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
        auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

        cgh.parallel_for<vector_add_3>(
            sycl::range{dataSize},
            [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
      });
    }  // Synchronize and copy-back

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}

TEST_CASE("usm_event_wait", "synchronization_solution") {
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

    auto devicePtrA = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrB = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrR = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};

    usmQueue.memcpy(devicePtrA, a,
                    sizeof(float) * dataSize)
        .wait();  // Synchronize
    usmQueue.memcpy(devicePtrB, b,
                    sizeof(float) * dataSize)
        .wait();  // Synchronize

    usmQueue
        .parallel_for<vector_add_4>(sycl::range{dataSize},
                                    [=](sycl::id<1> idx) {
                                      auto globalId = idx[0];
                                      devicePtrR[globalId] =
                                          devicePtrA[globalId] +
                                          devicePtrB[globalId];
                                    })
        .wait();  // Synchronize

    usmQueue.memcpy(r, devicePtrR,
                    sizeof(float) * dataSize)
        .wait();  // Synchronize and copy-back

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

TEST_CASE("usm_queue_wait", "synchronization_solution") {
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

    auto devicePtrA = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrB = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};
    auto devicePtrR = sycl::experimental::usm_wrapper<float>{
        sycl::malloc_device<float>(dataSize, usmQueue)};

    usmQueue.memcpy(devicePtrA, a, sizeof(float) * dataSize);
    usmQueue.memcpy(devicePtrB, b, sizeof(float) * dataSize);

    usmQueue.wait();  // Synchronize

    usmQueue.parallel_for<vector_add_5>(
        sycl::range{dataSize}, [=](sycl::id<1> idx) {
          auto globalId = idx[0];
          devicePtrR[globalId] = devicePtrA[globalId] + devicePtrB[globalId];
        });

    usmQueue.wait();  // Synchronize

    usmQueue.memcpy(r, devicePtrR,
                    sizeof(float) * dataSize)
        .wait();  // Copy-back

    usmQueue.wait();  // Synchronize

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

TEST_CASE("host_accessor", "synchronization_solution") {
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

    {
      auto bufA = sycl::buffer{a, sycl::range{dataSize}};
      auto bufB = sycl::buffer{b, sycl::range{dataSize}};
      auto bufR = sycl::buffer{r, sycl::range{dataSize}};

      gpuQueue.submit([&](sycl::handler& cgh) {
        auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
        auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
        auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

        cgh.parallel_for<vector_add_6>(
            sycl::range{dataSize},
            [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
      });

      gpuQueue.wait();  // Synchronize

      {
        auto hostAccR =
            bufR.get_access<sycl::access::mode::read>();  // Copy-to-host

        for (int i = 0; i < dataSize; ++i) {
          REQUIRE(hostAccR[i] == i * 2);
        }
      }

    }  // Copy-back

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }
}
