/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include "../helpers.hpp"

#include <sycl/sycl.hpp>

class vector_add_1;
class vector_add_2;

void test_item() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    auto gpuQueue = sycl::queue { sycl::gpu_selector_v };

    auto bufA = sycl::buffer { a, sycl::range { dataSize } };
    auto bufB = sycl::buffer { b, sycl::range { dataSize } };
    auto bufR = sycl::buffer { r, sycl::range { dataSize } };

    gpuQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accA { bufA, cgh, sycl::read_only };
      sycl::accessor accB { bufB, cgh, sycl::read_only };
      sycl::accessor accR { bufR, cgh, sycl::write_only };

      cgh.parallel_for<vector_add_1>(
          sycl::range { dataSize }, [=](sycl::item<1> itm) {
            auto globalId = itm.get_id();
            accR[globalId] = accA[globalId] + accB[globalId];
          });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    SYCLACADEMY_ASSERT(r[i] == i * 2);
  }
}

void test_nd_item() {
  constexpr size_t dataSize = 1024;
  constexpr size_t workGroupSize = 128;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {
    auto gpuQueue = sycl::queue { sycl::gpu_selector_v };

    auto bufA = sycl::buffer { a, sycl::range { dataSize } };
    auto bufB = sycl::buffer { b, sycl::range { dataSize } };
    auto bufR = sycl::buffer { r, sycl::range { dataSize } };

    gpuQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accA { bufA, cgh, sycl::read_write };
      sycl::accessor accB { bufB, cgh, sycl::read_write };
      sycl::accessor accR { bufR, cgh, sycl::read_write };

      auto ndRange = sycl::nd_range { sycl::range { dataSize },
                                      sycl::range { workGroupSize } };

      cgh.parallel_for<vector_add_2>(ndRange, [=](sycl::nd_item<1> itm) {
        auto globalId = itm.get_global_id();
        accR[globalId] = accA[globalId] + accB[globalId];
      });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    SYCLACADEMY_ASSERT(r[i] == i * 2);
  }
}

int main() {
  test_item();
  test_nd_item();
}
