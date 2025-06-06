/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <sycl/sycl.hpp>

#include "../helpers.hpp"

class kernel_a_1;
class kernel_b_1;
class kernel_c_1;
class kernel_d_1;
class kernel_a_2;
class kernel_b_2;
class kernel_c_2;
class kernel_d_2;

void test_buffer() {
  constexpr size_t dataSize = 1024;

  int inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = static_cast<float>(i);
    inB[i] = static_cast<float>(i);
    inC[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  try {
    auto defaultQueue = sycl::queue{};

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
      sycl::accessor accOut{bufInB, cgh, sycl::read_write};

      cgh.parallel_for<kernel_b_1>(sycl::range{dataSize}, [=](sycl::id<1> idx) {
        accOut[idx] += accIn[idx];
      });
    });

    defaultQueue.submit([&](sycl::handler& cgh) {
      sycl::accessor accIn{bufInA, cgh, sycl::read_only};
      sycl::accessor accOut{bufInC, cgh, sycl::read_write};

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

  SYCLACADEMY_ASSERT_EQUAL(out, [](size_t i) { return i * 2.0f; });
}

int main() {
  test_buffer();
}
