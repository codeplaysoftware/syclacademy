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

TEST_CASE("grayscale", "sycl_05_grayscale") {
  int width, height, channels;

  auto inputFile =
    std::string("<path-to-exercise-directory>/dogs.png");
  auto outputFile =
  std::string("<path-to-exercises-directory>/dogs_grayscale.png");

  unsigned char* rawInputData =
    stbi_load(inputFile.c_str(), &width, &height, &channels, 4);

  auto size = width * height * channels;

  auto imageData = std::vector<float>(size);

  for (int i = 0; i < (size); ++i) {
    imageData[i] = static_cast<float>(rawInputData[i]);
  }

  // ...

  cppcon::benchmark([&]() { /* ... */ }, 100, "grayscale");

  // ...

  unsigned char* rawOutputData = new unsigned char[size];
  for (int i = 0; i < (size); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(imageData[i]);
  }

  stbi_write_png(outputFile.c_str(), width, height, channels, rawOutputData, 0);

  delete[] rawOutputData;

  stbi_image_free(rawInputData);

  REQUIRE(true);
}
