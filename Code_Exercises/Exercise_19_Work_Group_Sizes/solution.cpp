/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <algorithm>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

#define STBI_NO_SIMD 1
#include <benchmark.h>
#include <image_conv.h>


class image_convolution;

inline constexpr util::filter_type filterType = util::filter_type::blur;
inline constexpr int filterWidth = 11;
inline constexpr int halo = filterWidth / 2;

TEST_CASE("image_convolution_work_group_sizes", "work_group_sizes_solution") {
  const char* inputImageFile =
      "../Images/dogs.png";
  const char* outputImageFile =
      "../Images/blurred_dogs.png";

  auto inputImage = util::read_image(inputImageFile, halo);

  auto outputImage = util::allocate_image(
      inputImage.width(), inputImage.height(), inputImage.channels());

  auto filter = util::generate_filter(util::filter_type::blur, filterWidth);

  try {
    sycl::queue myQueue{sycl::gpu_selector{},
                        [](sycl::exception_list exceptionList) {
                          for (auto e : exceptionList) {
                            std::rethrow_exception(e);
                          }
                        }};

    std::cout << "Running on "
              << myQueue.get_device().get_info<sycl::info::device::name>()
              << "\n";

    auto inputImgWidth = inputImage.width();
    auto inputImgHeight = inputImage.height();
    auto channels = inputImage.channels();
    auto filterWidth = filter.width();
    auto halo = filter.half_width();

    auto globalRange = sycl::range(inputImgWidth, inputImgHeight);
    auto localRange = sycl::range(16, 16);
    auto ndRange = sycl::nd_range(globalRange, localRange);

    auto inBufRange = (inputImgWidth + (halo * 2)) * sycl::range(1, channels);
    auto outBufRange = inputImgHeight * sycl::range(1, channels);
    auto filterRange = filterWidth * sycl::range(1, channels);
    auto scratchpadRange = localRange + sycl::range(halo * 2, halo * 2);

    {
      auto inBuf = sycl::buffer{inputImage.data(), inBufRange};
      auto outBuf = sycl::buffer<float, 2>{outBufRange};
      auto filterBuf = sycl::buffer{filter.data(), filterRange};
      outBuf.set_final_data(outputImage.data());

      auto inBufVec = inBuf.reinterpret<sycl::float4>(inBufRange /
                                                      sycl::range(1, channels));
      auto outBufVec = outBuf.reinterpret<sycl::float4>(
          outBufRange / sycl::range(1, channels));
      auto filterBufVec = filterBuf.reinterpret<sycl::float4>(
          filterRange / sycl::range(1, channels));

      util::benchmark(
          [&]() {
            myQueue.submit([&](sycl::handler& cgh) {
              auto inputAcc =
                  inBufVec.get_access<sycl::access::mode::read>(cgh);
              auto outputAcc =
                  outBufVec.get_access<sycl::access::mode::write>(cgh);
              auto filterAcc =
                  filterBufVec.get_access<sycl::access::mode::read>(cgh);

              auto scratchpad = sycl::accessor<sycl::float4, 2,
                                               sycl::access::mode::read_write,
                                               sycl::access::target::local>(
                  scratchpadRange, cgh);

              cgh.parallel_for<image_convolution>(
                  ndRange, [=](sycl::nd_item<2> item) {
                    auto globalId = item.get_global_id();
                    globalId = sycl::id{globalId[1], globalId[0]};
                    auto localId = item.get_local_id();

                    auto haloOffset = sycl::id(halo, halo);
                    auto src = (globalId + haloOffset);
                    auto dest = globalId;
                    auto temp = localId + halo;

                    scratchpad[temp] = inputAcc[src];

                    sycl::group_barrier(item.get_group());

                    auto sum = sycl::float4{0.0f, 0.0f, 0.0f, 0.0f};

                    for (int r = 0; r < filterWidth; ++r) {
                      for (int c = 0; c < filterWidth; ++c) {
                        auto srcOffset = sycl::id(temp[0] + (r - halo),
                                                  temp[1] + ((c - halo)));
                        auto filterOffset = sycl::id(r, c);

                        sum += scratchpad[srcOffset] * filterAcc[filterOffset];
                      }
                    }

                    outputAcc[dest] = sum;
                  });
            });

            myQueue.wait_and_throw();
          },
          100, "image convolution (tiled)");
    }
  } catch (sycl::exception e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  util::write_image(outputImage, outputImageFile);

  REQUIRE(true);
}
