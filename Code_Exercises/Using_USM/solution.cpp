/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <sycl/sycl.hpp>

#include "../helpers.hpp"

class vector_add;

int usm_selector(const sycl::device& dev) {
  if (dev.has(sycl::aspect::usm_device_allocations)) {
    return 1;
  }
  return -1;
}

int main() {
  constexpr size_t dataSize = 1024;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto usmQueue = sycl::queue{usm_selector};

    auto devicePtrA = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrB = sycl::malloc_device<float>(dataSize, usmQueue);
    auto devicePtrR = sycl::malloc_device<float>(dataSize, usmQueue);

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
    SYCLACADEMY_ASSERT(r[i] == i * 2);
  }
}
