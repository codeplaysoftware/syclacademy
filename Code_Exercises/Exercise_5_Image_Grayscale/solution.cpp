/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <benchmark.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <CL/sycl.hpp>

class naive;
class coalesced;
class vectorised;

TEST_CASE("naive", "sycl_05_grayscale") {
  int width, height, channels;

  auto inputFile =
    std::string("<path-to-exercise-directory>/dogs.png");
  auto outputFile =
    std::string("<path-to-exercise-directory>/dogs_grayscale_naive.png");

  unsigned char* rawInputData =
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

    defaultQueue.submit([&](cl::sycl::handler& cgh) {
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
  }

  unsigned char* rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}

TEST_CASE("coalesced", "sycl_05_grayscale") {
  int width, height, channels;

  auto inputFile =
    std::string("<path-to-exercises-directory>/dogs.png");
  auto outputFile =
    std::string("<path-to-exercises-directory>/dogs_grayscale_coalesced.png");

  unsigned char* rawInputData =
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
        defaultQueue.submit([&](cl::sycl::handler& cgh) {
          auto imageDataAcc =
            imageDataBuf
            .template get_access<cl::sycl::access::mode::read_write>(
              cgh);

          cgh.parallel_for<coalesced>(
            cl::sycl::range<2>(width, height), [=](cl::sycl::id<2> idx) {
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

  unsigned char* rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}

TEST_CASE("vectorise", "sycl_05_grayscale") {
  int width, height, channels;

  auto inputFile =
    std::string("<path-to-exercises-directory>/dogs.png");
  auto outputFile =
    std::string("<path-to-exercises-directory>/dogs_grayscale_vectorised.png");

  unsigned char* rawInputData =
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
        defaultQueue.submit([&](cl::sycl::handler& cgh) {
          auto imageDataAcc =
            imageDataVecBuf
            .template get_access<cl::sycl::access::mode::read_write>(
              cgh);

          cgh.parallel_for<vectorised>(
            cl::sycl::range<2>(width, height), [=](cl::sycl::id<2> idx) {
              auto linearId = (idx[0] * height) + idx[1];

              auto p = imageDataAcc[linearId];
              auto y = p.r() * 0.299f + p.g() * 0.587f + p.b() * 0.114f;
              imageDataAcc[linearId] = cl::sycl::float4{ y, y, y, p.a() };
            });
          });

        defaultQueue.wait_and_throw();
      },
      100, "vectorised");
  }

  unsigned char* rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}
