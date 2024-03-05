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

#include <sycl/sycl.hpp>

#include <benchmark.h>
#include <image_conv.h>

enum Direction
{
  COL,
  ROW
};
/**
 * @brief The ImageConvolutionFunctor class represents a functor for performing image convolution.
 * 
 * This class is templated on the data type of the image elements. It provides methods for setting 
 * the input and output buffers, setting the filter buffer, setting the SYCL handler, and 
 * performing the convolution operation. The convolution operation is performed by the operator() 
 * method, which takes a SYCL nd_item and a direction as input. The operator() method applies the 
 * convolution filter to the input image and stores the result in the output image buffer.
 * 
 * The ImageConvolutionFunctor class also contains private member variables for storing the filter, 
 * input, and output buffers, as well as accessors for these buffers. It also stores the halo size 
 * and filter width.
 */
template <typename dataT>
class ImageConvolutionFunctor
{

public:
  ImageConvolutionFunctor(sycl::buffer<dataT, 1> *filter) : filter_(filter)
  {
    filterWidth_ = filter_->get_range()[0];
    halo_ = filterWidth_ / 2;
    out_ = NULL;
  }
  ImageConvolutionFunctor()
  {
    filter_ = NULL;
    out_ = NULL;
  }
/**
 * @brief The operator method of the ImageConvolutionFunctor class performs image convolution
 *        using a given filter.
 * 
 * @details Takes a sycl::nd_item<2> object and a Direction enum as parameters.
 *        The method calculates the global ID of the item, initializes a sum variable, a filter offset,
 *        and a source offset based on the global ID and the halo size. 
 *        It then checks the direction parameter and performs the convolution operation accordingly.
 *        For the ROW direction, it iterates over the halo range and calculates the source offset for
 *        each row, and adds the product of the input accessor at the source offset and the filter
 *        accessor at the filter offset to the sum. For the COL direction, it iterates over the halo
 *        range and calculates the source offset for each column, and adds the product of the input
 *        accessor at the source offset and the filter accessor at the filter offset to the sum.
 *        Finally, it checks if the output accessor range is different from the input accessor range
 *        and assigns the sum to the output accessor  at the global ID (final buffer), or assigns
 *        the sum to the output accessor at the global ID plus the halo size (intermediate buffer).
 * 
 * @param item The sycl::nd_item<2> object representing the item being processed.
 * @param dir The Direction enum indicating the direction of the convolution operation (ROW or COL).
 */
  void operator()(sycl::nd_item<2> item, Direction dir) const
  {
    auto globalId = item.get_global_id();

    auto sum = dataT{0.0f, 0.0f, 0.0f, 0.0f};
    auto filterOffset = sycl::id(0);
    auto src = globalId + sycl::id(halo_, halo_);

    if (dir == Direction::ROW)
    {
      for (int r = -halo_; r < halo_ + 1; ++r)
      {
        auto srcOffset = sycl::id(src[0] + r, src[1]);
        sum += inputAcc_[srcOffset] * filterAcc_[filterOffset++];
      }
    }
    else
    {
      for (int c = -halo_; c < halo_ + 1; ++c)
      {
        auto srcOffset = sycl::id(src[0], src[1] + c);
        sum += inputAcc_[srcOffset] * filterAcc_[filterOffset++];
      }
    }

    if (outputAcc_.get_range() != inputAcc_.get_range())
      outputAcc_[globalId] = sum;
    else
      outputAcc_[globalId + sycl::id(halo_, halo_)] = sum;
  }

  void setBuffers(sycl::buffer<dataT, 2> &in, sycl::buffer<dataT, 2> &out, sycl::buffer<dataT, 1> &filter)
  {
    filter_ = &filter;
    in_ = &in;
    out_ = &out;
    filterWidth_ = filter_->get_range()[0];
    halo_ = filterWidth_ / 2;
  }

  void setBuffers(sycl::buffer<dataT, 2> &in, sycl::buffer<dataT, 2> &out)
  {

    if (filter_ == NULL)
      throw "The filter has to be set first.";

    in_ = &in;
    out_ = &out;
  }

  void setBuffers(sycl::buffer<dataT, 2> &out)
  {
    if (out_ == NULL)
      throw "No previous buffers defined.";

    in_ = out_;
    out_ = &out;
  }

  void setHandler(sycl::handler &cgh)
  {
    filterAcc_ = filter_->template get_access<sycl::access::mode::read>(cgh);
    inputAcc_ = in_->template get_access<sycl::access::mode::read>(cgh);
    outputAcc_ = out_->template get_access<sycl::access::mode::write>(cgh);
  }

private:
  sycl::buffer<dataT, 1> *filter_;
  sycl::buffer<dataT, 2> *in_;
  sycl::buffer<dataT, 2> *out_;
  sycl::accessor<dataT, 2, sycl::access::mode::read> inputAcc_;
  sycl::accessor<dataT, 2, sycl::access::mode::write> outputAcc_;
  sycl::accessor<dataT, 1, sycl::access::mode::read> filterAcc_;
  int halo_;
  int filterWidth_;
};

util::image_ref<float> linear_blur(int width)
{
  if (width % 2 == 0)
  {
    std::cerr << "Error: width has to be an odd number." << std::endl;
    exit(1);
  }

  int size = width * 4;

  float *filterData = new float[size];

  for (int i = 0; i < width; ++i)
  {
    auto index = i * 4;
    auto isCenter = (i == (width / 2));

    filterData[index + 0] = 1.0f / static_cast<float>(width);
    filterData[index + 1] = 1.0f / static_cast<float>(width);
    filterData[index + 2] = 1.0f / static_cast<float>(width);
    filterData[index + 3] = isCenter ? 1.0f : 0.0f;
  }

  return util::image_ref<float>{filterData, width, 1, 4, 0};
}

/**
 * @brief Run the kernel function.
 * 
 * It takes four parameters: ndRange, cgh, convolve, and dir.
 * - ndRange: A SYCL nd_range object representing the range of work items to be executed.
 * - cgh: A SYCL handler object used to set the handler for the convolve functor.
 * - convolve: An instance of the ImageConvolutionFunctor class templated on imageT.
 * - dir: An enum value representing the direction of the convolution operation.
 * 
 * The function sets the handler for the convolve functor using the setHandler method.
 * It then calls the parallel_for method of the handler to execute the convolution operation.
 * The lambda function passed to parallel_for calls the operator() method of the convolve functor
 * with the current nd_item and direction as arguments.
 * 
 * This function is used to perform image convolution using SYCL.
 */
template <typename imageT>
void kernelFunction(sycl::nd_range<2> ndRange, sycl::handler &cgh, ImageConvolutionFunctor<imageT> convolve, Direction dir)
{
  convolve.setHandler(cgh);

  cgh.parallel_for(ndRange, [=](sycl::nd_item<2> item)
                   { convolve(item, dir); });
}

inline constexpr util::filter_type filterType = util::filter_type::blur;
inline constexpr int filterWidth = 11;
inline constexpr int halo = filterWidth / 2;

TEST_CASE("image_convolution_1D", "1D_solution")
{
  const char *inputImageFile =
      "../Images/dogs.png";
  const char *outputImageFile =
      "../Images/blurred_dogs_1D.png";

  auto inputImage = util::read_image(inputImageFile, halo);

  auto outputImage = util::allocate_image(
      inputImage.width(), inputImage.height(), inputImage.channels());

  auto filter = linear_blur(filterWidth);

  try
  {
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
      auto filterBufVec = filterBuf.reinterpret<sycl::float4>(
          filterRange / channels);

      ImageConvolutionFunctor<sycl::float4> convolve(&filterBufVec);

      util::benchmark(
          [&]()
          {
            convolve.setBuffers(inBufVec, tempBufVec);
            myQueue.submit([&](sycl::handler &cgh) {
              kernelFunction<sycl::float4>(ndRange, cgh, convolve, Direction::ROW);
            });

            convolve.setBuffers(outBufVec);
            myQueue.submit([&](sycl::handler &cgh) {
              kernelFunction<sycl::float4>(ndRange, cgh, convolve, Direction::COL);
            });

            myQueue.wait_and_throw();
          },
          100, "image convolution (COL and ROW)");
    }
  }
  catch (sycl::exception e)
  {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  util::write_image(outputImage, outputImageFile);

  REQUIRE(true);
}
