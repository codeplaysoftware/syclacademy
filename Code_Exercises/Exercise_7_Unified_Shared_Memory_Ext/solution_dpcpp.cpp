/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/


#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CL/sycl.hpp>

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
void parallel_add(std::vector<T>& inputA, std::vector<T>& inputB,
  std::vector<T>& output) {

  assert((inputA.size() == inputB.size()) && (inputA.size() == output.size()));

  const auto size = inputA.size();
  const auto sizeInBytes = size * sizeof(T);

  auto usmQueue = queue{ usm_device_selector{} };

  auto inputAPtr = static_cast<T*>(malloc_device(sizeInBytes, usmQueue));
  auto inputBPtr = static_cast<T*>(malloc_device(sizeInBytes, usmQueue));
  auto outputPtr = static_cast<T*>(malloc_device(sizeInBytes, usmQueue));

  auto copyInputA = usmQueue.memcpy(inputAPtr, inputA.data(), sizeInBytes);
  auto copyInputB = usmQueue.memcpy(inputBPtr, inputB.data(), sizeInBytes);

  usmQueue.submit([&](handler &cgh) {
    cgh.depends_on(copyInputA);
    cgh.depends_on(copyInputB);

    cgh.parallel_for(range<1>(size), [=](id<1> idx) {
      outputPtr[idx] = inputAPtr[idx] + inputBPtr[idx];
    });
  }).wait();

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