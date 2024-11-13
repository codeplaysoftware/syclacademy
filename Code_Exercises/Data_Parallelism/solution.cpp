/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include "../helpers.hpp"
#include <sycl/sycl.hpp>

class vector_add;

int main() {
  constexpr size_t dataSize = 1024;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  try {
    auto defaultQueue = sycl::queue {};

    auto bufA = sycl::buffer { a, sycl::range { dataSize } };
    auto bufB = sycl::buffer { b, sycl::range { dataSize } };
    auto bufR = sycl::buffer { r, sycl::range { dataSize } };

    defaultQueue
        .submit([&](sycl::handler& cgh) {
          sycl::accessor accA { bufA, cgh, sycl::read_only };
          sycl::accessor accB { bufB, cgh, sycl::read_only };
          sycl::accessor accR { bufR, cgh, sycl::write_only };

          cgh.parallel_for<vector_add>(
              sycl::range { dataSize },
              [=](sycl::id<1> idx) { accR[idx] = accA[idx] + accB[idx]; });
        })
        .wait();

    defaultQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    SYCLACADEMY_ASSERT(r[i] == static_cast<float>(i) * 2.0f);
  }
}
