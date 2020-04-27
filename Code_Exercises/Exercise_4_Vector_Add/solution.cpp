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

template <typename T>
class add;

template <typename T>
void parallel_add(std::vector<T>& inputA, std::vector<T>& inputB,
  std::vector<T>& output) {
  using namespace cl::sycl;

  assert(inputA.size() == inputB.size() && inputA.size() == output.size());

  auto size = inputA.size();

  queue defaultQueue;

  buffer<T, 1> inputABuf(inputA.data(), range<1>(size));
  buffer<T, 1> inputBBuf(inputB.data(), range<1>(size));
  buffer<T, 1> outputBuf(output.data(), range<1>(size));

  defaultQueue.submit([&](handler& cgh) {
    auto inputAAcc = inputABuf.template get_access<access::mode::read>(cgh);
    auto inputBAcc = inputBBuf.template get_access<access::mode::read>(cgh);
    auto outputAcc = outputBuf.template get_access<access::mode::write>(cgh);

    cgh.parallel_for<add<T>>(range<1>(size), [=](id<1> i) {
      outputAcc[i] = inputAAcc[i] + inputBAcc[i];
      });
    });
}

TEST_CASE("add_floats", "sycl_04_vector_add") {
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

TEST_CASE("intermediate_buffer", "sycl_04_vector_add") {
  const int size = 1024;

  std::vector<float> inputA(size);
  std::vector<float> inputB(size);
  std::vector<float> inputC(size);
  std::vector<float> temp(size);
  std::vector<float> output(size);

  std::iota(begin(inputA), end(inputA), 0.0f);
  std::iota(begin(inputB), end(inputB), 0.0f);
  std::iota(begin(inputC), end(inputC), 0.0f);
  std::fill(begin(temp), end(temp), 0.0f);
  std::fill(begin(output), end(output), 0.0f);

  parallel_add(inputA, inputB, temp);

  parallel_add(temp, inputC, output);

  for (int i = 0; i < size; i++) {
    REQUIRE(output[i] == static_cast<float>(i * 3.0f));
  }
}
