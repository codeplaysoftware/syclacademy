/*
 SYCL Academy (c)
 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.
 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#ifndef __IMAGE_CONV_H__
#define __IMAGE_CONV_H__

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace util {

enum class filter_type {
  identity,
  blur
};

template <typename T>
class image_ref {
 public:
  image_ref(T* imageData, int width, int height, int channels, int halo)
      : imageData_{imageData},
        width_{width},
        height_{height},
        channels_{channels},
        halo_{halo} {}

  ~image_ref() { delete[] imageData_; }

  T* data() const noexcept { return imageData_; }

  int width() const noexcept { return width_; }

  int height() const noexcept { return height_; }

  int channels() const noexcept { return channels_; }

  int halo() const noexcept { return halo_; }

  int count() const noexcept { return width_ * height_; }

  int size() const noexcept { return width_ * height_ * channels_; }

  int half_width() const noexcept { return width_ / 2; }

 private:
  T* imageData_ = nullptr;
  int width_ = 0;
  int height_ = 0;
  int channels_ = 0;
  int halo_ = 0;
};

image_ref<float> read_image(std::string imageFile, int halo) {
  int width = 0, height = 0, channels = 0;
  unsigned char* inputData =
      stbi_load(imageFile.c_str(), &width, &height, &channels, 0);

#ifdef MYDEBUGS
  if (inputData == nullptr) {
    std::cerr << "File " << imageFile << " cannot be found and loaded.\n";
    exit(1);
  }
#endif

  assert(inputData != nullptr);

  int widthWithPadding = width + (halo * 2);
  int heightWithPadding = height + (halo * 2);

  int sizeWithPadding = (width + (halo * 2)) * (height + (halo * 2)) * channels;

  float* imageData = new float[sizeWithPadding];

  for (int i = 0; i < (heightWithPadding); ++i) {
    for (int j = 0; j < (widthWithPadding); ++j) {
      for (int c = 0; c < channels; ++c) {
        int srcI = i - halo;
        int srcJ = j - halo;

        srcJ = std::clamp(srcJ, 0, (width - 1));
        srcI = std::clamp(srcI, 0, (height - 1));

        int srcIndex = (srcI * width * channels) + (srcJ * channels) + c;
        int destIndex = (i * widthWithPadding * channels) + (j * channels) + c;

        imageData[destIndex] = static_cast<float>(inputData[srcIndex]);
      }
    }
  }

  stbi_image_free(inputData);

  return image_ref<float>{imageData, width, height, channels, halo};
}

image_ref<float> allocate_image(int width, int height, int channels) {
  float* imageData = new float[width * height * channels];

  return image_ref<float>{imageData, width, height, channels, 0};
}

template <typename T>
void write_image(const image_ref<T>& image, std::string imageFile) {
  unsigned char* rawOutputData = new unsigned char[image.size()];
  for (int i = 0; i < image.size(); ++i) {
    rawOutputData[i] = static_cast<unsigned char>(image.data()[i]);
  }

  stbi_write_png(imageFile.c_str(), image.width(), image.height(),
                 image.channels(), rawOutputData, 0);
}

  image_ref<float> generate_filter(filter_type filterType, int width, int channels) {
  int count = width * width;
  int size = count * channels;

  assert( channels > 0 );
  assert( channels <= 4 );

  float* filterData = new float[size];
  
  for (int j = 0; j < width; ++j) {
    for (int i = 0; i < width; ++i) {
      auto index = ((j * width * channels) + (i * channels));
      auto isCenter = (j == (width / 2) && i == (width / 2));
      switch (filterType) {
        case filter_type::identity:
          filterData[index + 0] = isCenter ? 1.0f : 0.0f;
	  if (channels>1)
	    filterData[index + 1] = isCenter ? 1.0f : 0.0f;
	  if (channels>2)
	    filterData[index + 2] = isCenter ? 1.0f : 0.0f;
	  if (channels>3)
	    filterData[index + 3] = isCenter ? 1.0f : 0.0f;
          break;
        case filter_type::blur:
          filterData[index + 0] = 1.0f / static_cast<float>(count);
	  if (channels>1)
	    filterData[index + 1] = 1.0f / static_cast<float>(count);
	  if (channels>2)
	    filterData[index + 2] = 1.0f / static_cast<float>(count);
	  if (channels>3)
	    filterData[index + 3] = isCenter ? 1.0f : 0.0f;
          break;
      }
    }
  }

  return image_ref<float>{filterData, width, width, channels, 0};
}

}  // namespace util

#endif  // __IMAGE_CONV_H__
