/*
Copyright 2019 Gordon Brown

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <CL/sycl.hpp>

#include <numeric>

template <typename T>
class add;

template <typename T>
void parallel_add(std::vector<T> &inputA, std::vector<T> &inputB,
                  std::vector<T> &output) {
  using namespace cl::sycl;

  assert(inputA.size() == inputB.size() && inputA.size() == output.size());

  auto size = inputA.size();

  queue defaultQueue;

  buffer<T, 1> inputABuf(inputA.data(), range<1>(size));
  buffer<T, 1> inputBBuf(inputB.data(), range<1>(size));
  buffer<T, 1> outputBuf(output.data(), range<1>(size));

  defaultQueue.submit([&](handler &cgh) {
    auto inputAAcc = inputABuf.template get_access<access::mode::read>(cgh);
    auto inputBAcc = inputBBuf.template get_access<access::mode::read>(cgh);
    auto outputAcc = outputBuf.template get_access<access::mode::write>(cgh);

    cgh.parallel_for<add<T>>(range<1>(size), [=](id<1> i) {
      outputAcc[i] = inputAAcc[i] + inputBAcc[i];
    });
  });
}

TEST_CASE("add_floats", "sycl_03_vector_add") {
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

TEST_CASE("intermediate_buffer", "sycl_03_vector_add") {
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
