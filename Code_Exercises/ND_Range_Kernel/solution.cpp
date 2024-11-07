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

class vector_add_1;
class vector_add_2;

TEST_CASE("range_kernel_with_item", "nd_range_kernel_solution") {
  constexpr size_t dataSize = 2<<20;

  try {
    auto gpuQueue = sycl::queue{sycl::gpu_selector_v};

    auto ptrA = sycl::malloc_shared<int>(dataSize, gpuQueue);
    auto ptrB = sycl::malloc_shared<int>(dataSize, gpuQueue);
    auto ptrR = sycl::malloc_shared<int>(dataSize, gpuQueue);

    for (int i = 0; i < dataSize; ++i) {
      ptrA[i] = i;
      ptrB[i] = i;
      ptrR[i] = 0;
    }

    gpuQueue.
      parallel_for<vector_add_1>(sycl::range{dataSize},
        [=](sycl::item<1> itm) {
          auto globalId = itm.get_id();
          ptrR[globalId] = ptrA[globalId] + ptrB[globalId];
    }).wait();

    for (int i = 0; i < dataSize; ++i) {
      REQUIRE(ptrR[i] == i * 2);
    }

    sycl::free(ptrA, gpuQueue);
    sycl::free(ptrB, gpuQueue);
    sycl::free(ptrR, gpuQueue);
    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
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
    auto gpuQueue = sycl::queue{sycl::gpu_selector_v};

    auto ptrA = sycl::malloc_device<int>(dataSize, gpuQueue);
    auto ptrB = sycl::malloc_device<int>(dataSize, gpuQueue);
    auto ptrR = sycl::malloc_device<int>(dataSize, gpuQueue);

    gpuQueue.memcpy(ptrA, a, sizeof(int) * dataSize);
    gpuQueue.memcpy(ptrB, b, sizeof(int) * dataSize);

    gpuQueue.wait();

    auto ndRange =
        sycl::nd_range{sycl::range{dataSize}, sycl::range{workGroupSize}};
    auto event = gpuQueue.parallel_for<vector_add_2>(ndRange,
      [=](sycl::nd_item<1> itm) {
        auto globalId = itm.get_global_id();
        ptrR[globalId] = ptrA[globalId] + ptrB[globalId];
    });

    // Depends on the vector add kernel.
    gpuQueue.memcpy(r, ptrR, sizeof(int) * dataSize, event).wait();

    sycl::free(ptrA, gpuQueue);
    sycl::free(ptrB, gpuQueue);
    sycl::free(ptrR, gpuQueue);
    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}
