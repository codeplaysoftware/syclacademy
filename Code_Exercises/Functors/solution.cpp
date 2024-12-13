/*
   SYCL Academy (c)

   SYCL Academy is licensed under a Creative Commons
   Attribution-ShareAlike 4.0 International License.

   You should have received a copy of the license along with this
   work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
 */

#include <benchmark.h>
#include <image_conv.h>

#include <algorithm>
#include <iostream>

#include <sycl/sycl.hpp>

#include "../helpers.hpp"

enum Direction { COL, ROW };

/**
 * @brief ImageConvolutionFunctor class
 *
 * This class represents a functor for performing image convolution. It takes
 * an input accessor, an output accessor, a filter accessor, and a direction
 * as input parameters. The functor applies the convolution operation on the
 * input image using the provided filter and stores the result in the output
 * image. The direction parameter determines whether the convolution is
 * performed along the rows or columns of the image.
 *
 * @tparam dataT The data type of the image elements
 */
template <typename dataT>
class ImageConvolutionFunctor {
 public:
  /**
   * @brief ImageConvolutionFunctor constructor
   *
   * This constructor initializes an ImageConvolutionFunctor object with the
   * provided input accessor, output accessor, filter accessor, and direction.
   * It also calculates the filter width and the halo size based on the filter
   * accessor.
   *
   * @tparam dataT The data type of the image elements
   * @param cgh the queue handler
   * @param in The input buffer for the image
   * @param out The output buffer for the image
   * @param filter The filter buffer for the convolution operation
   * @param dir The direction of the convolution operation (ROW or COL)
   */
  ImageConvolutionFunctor<dataT>(sycl::handler& cgh, sycl::buffer<dataT, 2>& in,
                                 sycl::buffer<dataT, 2>& out,
                                 sycl::buffer<dataT, 1>& filter,
                                 const Direction& dir)
      : inputAcc_{in, cgh, sycl::read_only},
        outputAcc_{out, cgh, sycl::write_only},
        filterAcc_{filter, cgh, sycl::read_only},
        dir_(dir) {
    filterWidth_ = filterAcc_.size();
    halo_ = filterWidth_ / 2;
  }

  /**
   * @brief ImageConvolutionFunctor operator
   *
   * This operator performs the image convolution operation using the provided
   * input accessor, output accessor, filter accessor, and direction. It
   * calculates the sum of the convolution operation for each pixel and stores
   * the result in the output image. The direction parameter determines whether
   * the convolution is performed along the rows or columns of the image.
   *
   * @tparam dataT The data type of the image elements
   * @param item The nd_item representing the current work item
   */
  void operator()(sycl::nd_item<2> item) const {
    auto globalId = item.get_global_id();

    auto sum = dataT{0.0f, 0.0f, 0.0f, 0.0f};
    auto filterOffset = sycl::id(0);
    auto src = globalId + sycl::id(halo_, halo_);

    if (dir_ == Direction::ROW) {
      for (int r = -halo_; r < halo_ + 1; ++r) {
        auto srcOffset = sycl::id(src[0] + r, src[1]);
        sum += inputAcc_[srcOffset] * filterAcc_[filterOffset++];
      }
    } else {
      for (int c = -halo_; c < halo_ + 1; ++c) {
        auto srcOffset = sycl::id(src[0], src[1] + c);
        sum += inputAcc_[srcOffset] * filterAcc_[filterOffset++];
      }
    }

    if (outputAcc_.get_range() != inputAcc_.get_range())
      outputAcc_[globalId] = sum;
    else
      outputAcc_[globalId + sycl::id(halo_, halo_)] = sum;
  }

 private:
  sycl::accessor<dataT, 2, sycl::access::mode::read> inputAcc_;
  sycl::accessor<dataT, 2, sycl::access::mode::write> outputAcc_;
  sycl::accessor<dataT, 1, sycl::access::mode::read> filterAcc_;
  int halo_;
  int filterWidth_;
  Direction dir_ = ROW;
};

util::image_ref<float> linear_blur(int width) {
  if (width % 2 == 0) {
    std::cerr << "Error: width has to be an odd number." << std::endl;
    exit(1);
  }

  int size = width * 4;

  float* filterData = new float[size];

  for (int i = 0; i < width; ++i) {
    auto index = i * 4;
    auto isCenter = (i == (width / 2));

    filterData[index + 0] = 1.0f / static_cast<float>(width);
    filterData[index + 1] = 1.0f / static_cast<float>(width);
    filterData[index + 2] = 1.0f / static_cast<float>(width);
    filterData[index + 3] = isCenter ? 1.0f : 0.0f;
  }

  return util::image_ref<float>{filterData, width, 1, 4, 0};
}

inline constexpr util::filter_type filterType = util::filter_type::blur;
inline constexpr int filterWidth = 11;
inline constexpr int halo = filterWidth / 2;

int main() {
  const char* inputImageFile = "../Images/dogs.png";
  const char* outputImageFile = "../Images/blurred_dogs_1D.png";

  auto inputImage = util::read_image(inputImageFile, halo);

  auto outputImage = util::allocate_image(
      inputImage.width(), inputImage.height(), inputImage.channels());

  auto filter = linear_blur(filterWidth);

  try {
    sycl::queue myQueue{sycl::cpu_selector_v};

    std::cout << "Running on "
              << myQueue.get_device().get_info<sycl::info::device::name>()
              << "\n";

    auto inputImgWidth = inputImage.width();
    auto inputImgHeight = inputImage.height();
    auto channels = inputImage.channels();
    auto filterWidth = filter.width();
    auto halo = filter.half_width();

    auto globalRange = sycl::range(inputImgWidth, inputImgHeight);
    auto localRange = sycl::range(1, 32);
    auto ndRange = sycl::nd_range(globalRange, localRange);

    auto inBufRange =
        sycl::range(inputImgHeight + (halo * 2), inputImgWidth + (halo * 2)) *
        sycl::range(1, channels);
    auto outBufRange =
        sycl::range(inputImgHeight, inputImgWidth) * sycl::range(1, channels);
    auto filterRange = sycl::range(filterWidth * channels);

    {
      auto inBuf = sycl::buffer{inputImage.data(), inBufRange};
      auto outBuf = sycl::buffer<float, 2>{outBufRange};
      auto tempBuf = sycl::buffer<float, 2>{inBufRange};
      auto filterBuf = sycl::buffer{filter.data(), filterRange};
      outBuf.set_final_data(outputImage.data());

      auto inBufVec = inBuf.reinterpret<sycl::float4>(inBufRange /
                                                      sycl::range(1, channels));
      auto tempBufVec = tempBuf.reinterpret<sycl::float4>(
          inBufRange / sycl::range(1, channels));
      auto outBufVec = outBuf.reinterpret<sycl::float4>(
          outBufRange / sycl::range(1, channels));
      auto filterBufVec =
          filterBuf.reinterpret<sycl::float4>(filterRange / channels);

      util::benchmark(
          [&]() {
            myQueue.submit([&](sycl::handler& cgh) {
              ImageConvolutionFunctor<sycl::float4> convolve(
                  cgh, inBufVec, tempBufVec, filterBufVec, Direction::ROW);
              cgh.parallel_for(ndRange, convolve);
            });

            myQueue.submit([&](sycl::handler& cgh) {
              ImageConvolutionFunctor<sycl::float4> convolve(
                  cgh, tempBufVec, outBufVec, filterBufVec, Direction::COL);
              cgh.parallel_for(ndRange, convolve);
            });

            myQueue.wait_and_throw();
          },
          100, "image convolution (COL and ROW)");
    }
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  util::write_image(outputImage, outputImageFile);

  SYCLACADEMY_ASSERT(true);
}
