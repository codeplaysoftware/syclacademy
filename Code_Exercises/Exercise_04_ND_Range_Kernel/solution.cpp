/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

#include <iostream>

class vector_add_1;
class vector_add_2;

int main() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  try {

    auto gpuQueue = sycl::queue{};

    auto bufA = sycl::buffer{a, sycl::range{dataSize}};
    auto bufB = sycl::buffer{b, sycl::range{dataSize}};
    auto bufR = sycl::buffer{r, sycl::range{dataSize}};

    auto my_nd = sycl::nd_range{sycl::range{1024}, sycl::range{32}};

    gpuQueue.submit([&](sycl::handler& cgh) {
      auto accA = sycl::accessor{bufA, cgh, sycl::read_only};
      auto accB = sycl::accessor{bufB, cgh, sycl::read_only};
      auto accR = sycl::accessor{bufR, cgh, sycl::write_only};

      cgh.parallel_for<vector_add_1>(
          my_nd, [=](sycl::nd_item<1> itm) {
            auto globalId = itm.get_global_id();
            accR[globalId] = accA[globalId] + accB[globalId];
          });
    });

    gpuQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  for (int i = 0; i < dataSize; ++i) {
    assert(r[i] == i * 2);
  }
  std::cout << "The vector add results were correct!\n";
}

