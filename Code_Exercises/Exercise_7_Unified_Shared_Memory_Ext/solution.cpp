/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define SYCL_ACADEMY_USING_COMPUTECPP

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#ifdef SYCL_ACADEMY_USING_COMPUTECPP
#include <SYCL/experimental/usm_wrapper.h>
#include <CL/sycl.hpp>
#include <SYCL/experimental.hpp>
#define depends_on experimental_depends_on
using namespace cl::sycl::experimental;
#else  // SYCL_ACADEMY_USING_COMPUTECPP
#include <CL/sycl.hpp>
#endif  // SYCL_ACADEMY_USING_COMPUTECPP

#include <numeric>

using namespace cl::sycl;

struct usm_device_selector : public cl::sycl::device_selector {
  int operator()(const cl::sycl::device& d) const override {
    if (d.get_info<info::device::usm_device_allocations>()) {
      return 1;
    }
    else {
      return -1;
    }
  }
};

template <typename T>
class add;

template <typename T>
void parallel_add(std::vector<T>& inputA, std::vector<T>& inputB,
  std::vector<T>& output) {

  assert((inputA.size() == inputB.size()) && (inputA.size() == output.size()));

  const auto size = inputA.size();
  const auto sizeInBytes = size * sizeof(T);

  auto usmQueue = queue{ usm_device_selector{} };

  auto inputAPtr = malloc_device<T>(size, usmQueue);
  auto inputBPtr = malloc_device<T>(size, usmQueue);
  auto outputPtr = malloc_device<T>(size, usmQueue);

  auto copyInputA = usmQueue.memcpy(inputAPtr, inputA.data(), sizeInBytes);
  auto copyInputB = usmQueue.memcpy(inputBPtr, inputB.data(), sizeInBytes);
  auto fillOutput = usmQueue.fill(outputPtr, 0, size);

  {
    // TODO(Gordon): Switch to usm_wrapper
#ifdef SYCL_ACADEMY_USING_COMPUTECPP
    usm_wrapper<T> inputAPtr = usm_wrapper<T>{ inputAPtr };
    usm_wrapper<T> inputBPtr = usm_wrapper<T>{ inputBPtr };
    usm_wrapper<T> outputPtr = usm_wrapper<T>{ outputPtr };
#endif  // SYCL_ACADEMY_USING_COMPUTECPP

    usmQueue.submit([&](handler& cgh) {

      cgh.depends_on(copyInputA);
      cgh.depends_on(copyInputB);
      cgh.depends_on(fillOutput);

      cgh.parallel_for<add<T>>(range<1>(size), [=](id<1> idx) {
        auto index = idx[0];
        outputPtr[index] = inputAPtr[index] + inputBPtr[index];
        });

      }).wait();
  }

  usmQueue.memcpy(output.data(), outputPtr, sizeInBytes).wait();
}

TEST_CASE("parallel_for_usm", "sycl_07_unified_shared_memory_ext") {
  const int size = 1024;

  std::vector<float> inputA(size);
  std::vector<float> inputB(size);
  std::vector<float> output(size);

  std::iota(begin(inputA), end(inputA), 0.0f);
  std::iota(begin(inputB), end(inputB), 0.0f);
  std::fill(begin(output), end(output), 0.0f);

  parallel_add(inputA, inputB, output);

  for (int i = 0; i < size; i++) {
    REQUIRE(output[i] == static_cast<float>(i * 2.0f));
  }
}
