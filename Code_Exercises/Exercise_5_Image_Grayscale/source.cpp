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
#include <catch2/catch.hpp>

#include <benchmark.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <CL/sycl.hpp>

TEST_CASE("grayscale", "sycl_04_grayscale") {
  int width, height, channels;

  auto inputFile =
      std::string("<path-to-repo>/cppcon-parallelism-class/resources/dogs.png");
  auto outputFile = std::string(
      "<path-to-repo>/cppcon-parallelism-class/resources/"
      "dogs_grayscale."
      "png");

  unsigned char *rawInputData =
      stbi_load(inputFile.c_str(), &width, &height, &channels, 4);

  auto size = width * height * channels;

  auto imageData = std::vector<float>(size);

  for (int i = 0; i < (size); ++i) {
    imageData[i] = static_cast<float>(rawInputData[i]);
  }

  // ...

  cppcon::benchmark([&]() { /* ... */ }, 100, "grayscale");

  // ...

  unsigned char *rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}