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

#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <CL/sycl.hpp>

class naive;
class coalesced;
class vectorised;

TEST_CASE("naive", "sycl_04_grayscale") {
  int width, height, channels;

  auto inputFile =
      std::string("<path-to-repo>/cppcon-parallelism-class/resources/dogs.png");
  auto outputFile = std::string(
      "<path-to-repo>/cppcon-parallelism-class/resources/"
      "dogs_grayscale_naive."
      "png");

  unsigned char *rawInputData =
      stbi_load(inputFile.c_str(), &width, &height, &channels, 4);

  if (!rawInputData) {
    return;
  }

  auto size = width * height * channels;

  auto imageData = std::vector<float>(size);

  for (int i = 0; i < (size); ++i) {
    imageData[i] = static_cast<float>(rawInputData[i]);
  }

  cl::sycl::queue defaultQueue;

  {
    cl::sycl::buffer<float, 1> imageDataBuf(imageData.data(), size);

    cppcon::benchmark(
        [&]() {
          defaultQueue.submit([&](cl::sycl::handler &cgh) {
            auto imageDataAcc =
                imageDataBuf
                    .template get_access<cl::sycl::access::mode::read_write>(
                        cgh);

            cgh.parallel_for<naive>(
                cl::sycl::range<2>(width, height), [=](cl::sycl::id<2> idx) {
                  auto linearId =
                      (idx[1] * width * channels) + (idx[0] * channels);

                  float y = (imageDataAcc[linearId] * 0.299f) +
                            (imageDataAcc[linearId + 1] * 0.587f) +
                            (imageDataAcc[linearId + 2] * 0.114f);
                  imageDataAcc[linearId] = y;
                  imageDataAcc[linearId + 1] = y;
                  imageDataAcc[linearId + 2] = y;
                });
          });

          defaultQueue.wait_and_throw();
        },
        100, "naive");
  }

  unsigned char *rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}

TEST_CASE("coalesced", "sycl_04_grayscale") {
  int width, height, channels;

  auto inputFile =
      std::string("<path-to-repo>/cppcon-parallelism-class/resources/dogs.png");
  auto outputFile = std::string(
      "<path-to-repo>/cppcon-parallelism-class/resources/"
      "dogs_grayscale_coalesced."
      "png");

  unsigned char *rawInputData =
      stbi_load(inputFile.c_str(), &width, &height, &channels, 4);

  if (!rawInputData) {
    return;
  }

  auto size = width * height * channels;

  auto imageData = std::vector<float>(size);

  for (int i = 0; i < (size); ++i) {
    imageData[i] = static_cast<float>(rawInputData[i]);
  }

  cl::sycl::queue defaultQueue;

  {
    cl::sycl::buffer<float, 1> imageDataBuf(imageData.data(), size);

    cppcon::benchmark(
        [&]() {
          defaultQueue.submit([&](cl::sycl::handler &cgh) {
            auto imageDataAcc =
                imageDataBuf
                    .template get_access<cl::sycl::access::mode::read_write>(
                        cgh);

            cgh.parallel_for<coalesced>(
                cl::sycl::range<2>(width, height), [=](cl::sycl::id<1> idx) {
                  auto linearId =
                      (idx[0] * height * channels) + (idx[1] * channels);

                  float y = (imageDataAcc[linearId] * 0.299f) +
                            (imageDataAcc[linearId + 1] * 0.587f) +
                            (imageDataAcc[linearId + 2] * 0.114f);
                  imageDataAcc[linearId] = y;
                  imageDataAcc[linearId + 1] = y;
                  imageDataAcc[linearId + 2] = y;
                });
          });

          defaultQueue.wait_and_throw();
        },
        100, "coalesced");
  }

  unsigned char *rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}

TEST_CASE("vectorise", "sycl_04_grayscale") {
  int width, height, channels;

  auto inputFile =
      std::string("<path-to-repo>/cppcon-parallelism-class/resources/dogs.png");
  auto outputFile = std::string(
      "<path-to-repo>/cppcon-parallelism-class/resources/"
      "dogs_grayscale_vectorised."
      "png");

  unsigned char *rawInputData =
      stbi_load(inputFile.c_str(), &width, &height, &channels, 4);

  if (!rawInputData) {
    return;
  }

  auto size = width * height * channels;

  auto imageData = std::vector<float>(size);

  for (int i = 0; i < (size); ++i) {
    imageData[i] = static_cast<float>(rawInputData[i]);
  }

  cl::sycl::queue defaultQueue;

  {
    cl::sycl::buffer<float, 1> imageDataBuf(imageData.data(), size);

    auto imageDataVecBuf = imageDataBuf.reinterpret<cl::sycl::float4>(
        cl::sycl::range<1>(size / channels));

    cppcon::benchmark(
        [&]() {
          defaultQueue.submit([&](cl::sycl::handler &cgh) {
            auto imageDataAcc =
                imageDataVecBuf
                    .template get_access<cl::sycl::access::mode::read_write>(
                        cgh);

            cgh.parallel_for<vectorised>(
                cl::sycl::range<2>(width, height), [=](cl::sycl::id<2> idx) {
                  auto linearId = (idx[0] * height) + idx[1];

                  auto p = imageDataAcc[linearId];
                  auto y = p.r() * 0.299f + p.g() * 0.587f + p.b() * 0.114f;
                  imageDataAcc[linearId] = cl::sycl::float4{y, y, y, p.a()};
                });
          });

          defaultQueue.wait_and_throw();
        },
        100, "vectorised");
  }

  unsigned char *rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}