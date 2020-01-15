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

#include <benchmark.h>

#include <iostream>
#include <iterator>
#include <numeric>

#include <CL/sycl.hpp>

class naive;
class local_mem;

static constexpr int WIDTH = 128;
static constexpr int HEIGHT = 128;
static constexpr int WORK_GROUP_WIDTH = 16;
static constexpr int WORK_GROUP_HEIGHT = 16;

template <typename T, int W, int H>
class matrix {
 public:
  void print() const noexcept {
    for (int r = 0; r < H; ++r) {
      for (int c = 0; c < W; ++c) {
        std::cout << data_[(r * W) + c] << ", ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  T *data() noexcept { return data_; }

  T *begin() noexcept { return data_; }

  T *end() noexcept { return &(data_[W * H]); }

  size_t size() const noexcept { return W * H; }

  size_t width() const noexcept { return W; }

  size_t height() const noexcept { return H; }

 private:
  T data_[W * H];
};

TEST_CASE("naive", "sycl_05_transpose") {
  auto inputMat = matrix<float, WIDTH, HEIGHT>{};
  auto outputMat = matrix<float, WIDTH, HEIGHT>{};

  std::iota(inputMat.begin(), inputMat.end(), 0.0f);
  std::fill(outputMat.begin(), outputMat.end(), 0.0f);

  // inputMat.print();
  // outputMat.print();

  cl::sycl::queue defaultQueue;

  {
    cl::sycl::buffer<float, 1> inputMatBuf(inputMat.data(), inputMat.size());
    cl::sycl::buffer<float, 1> outputMatBuf(outputMat.data(), outputMat.size());

    cppcon::benchmark(
        [&]() {
          defaultQueue.submit([&](cl::sycl::handler &cgh) {
            auto inputMatAcc =
                inputMatBuf.template get_access<cl::sycl::access::mode::read>(
                    cgh);
            auto outputMatAcc =
                outputMatBuf.template get_access<cl::sycl::access::mode::write>(
                    cgh);

            cgh.parallel_for<naive>(
                cl::sycl::range<2>(inputMat.width(), inputMat.height()),
                [=](cl::sycl::id<1> idx) {
                  auto rowMajorId = (idx[1] * inputMat.width()) + idx[0];
                  auto columnMajorId = (idx[0] * inputMat.height()) + idx[1];

                  outputMatAcc[rowMajorId] = inputMatAcc[columnMajorId];
                });
          });

          defaultQueue.wait_and_throw();
        },
        100, "naive");
  }

  // inputMat.print();
  // outputMat.print();

  REQUIRE(true);
}

TEST_CASE("local_mem", "sycl_05_transpose") {
  auto inputMat = matrix<float, WIDTH, HEIGHT>{};
  auto outputMat = matrix<float, WIDTH, HEIGHT>{};

  std::iota(inputMat.begin(), inputMat.end(), 0.0f);
  std::fill(outputMat.begin(), outputMat.end(), 0.0f);

  // inputMat.print();
  // outputMat.print();

  cl::sycl::queue defaultQueue;

  {
    cl::sycl::buffer<float, 1> inputMatBuf(inputMat.data(), inputMat.size());
    cl::sycl::buffer<float, 1> outputMatBuf(outputMat.data(), outputMat.size());

    cppcon::benchmark(
        [&]() {
          defaultQueue.submit([&](cl::sycl::handler &cgh) {
            auto inputMatAcc =
                inputMatBuf.template get_access<cl::sycl::access::mode::read>(
                    cgh);
            auto outputMatAcc =
                outputMatBuf.template get_access<cl::sycl::access::mode::write>(
                    cgh);

            auto scratchpad =
                cl::sycl::accessor<float, 1, cl::sycl::access::mode::read_write,
                                   cl::sycl::access::target::local>(
                    cl::sycl::range<1>(WORK_GROUP_WIDTH * WORK_GROUP_HEIGHT),
                    cgh);

            cgh.parallel_for<local_mem>(
                cl::sycl::nd_range<2>(
                    cl::sycl::range<2>(inputMat.width(), inputMat.height()),
                    cl::sycl::range<2>(WORK_GROUP_WIDTH, WORK_GROUP_HEIGHT)),
                [=](cl::sycl::nd_item<1> item) {
                  auto columnMajorId =
                      (item.get_global_id(1) * item.get_global_range(0)) +
                      item.get_global_id(0);

                  auto rowMajorLocalId =
                      (item.get_local_id(0) * item.get_local_range(1)) +
                      item.get_local_id(1);
                  auto columnMajorLocalId =
                      (item.get_local_id(1) * item.get_local_range(0)) +
                      item.get_local_id(0);

                  scratchpad[columnMajorLocalId] = inputMatAcc[columnMajorId];

                  item.barrier(cl::sycl::access::fence_space::global_and_local);

                  outputMatAcc[columnMajorId] = scratchpad[rowMajorLocalId];
                });
          });

          defaultQueue.wait_and_throw();
        },
        100, "local_mem");
  }

  // inputMat.print();
  // outputMat.print();

  REQUIRE(true);
}
