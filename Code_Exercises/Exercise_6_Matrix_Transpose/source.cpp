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

#include <iostream>
#include <iterator>
#include <numeric>

#include <CL/sycl.hpp>

static constexpr int WIDTH = 128;
static constexpr int HEIGHT = 128;

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

  T* data() noexcept { return data_; }

  T* begin() noexcept { return data_; }

  T* end() noexcept { return &(data_[W * H]); }

  size_t size() const noexcept { return W * H; }

  size_t width() const noexcept { return W; }

  size_t height() const noexcept { return H; }

private:
  T data_[W * H];
};

TEST_CASE("transpose", "sycl_05_transpose") {
  auto inputMat = matrix<float, WIDTH, HEIGHT>{};
  auto outputMat = matrix<float, WIDTH, HEIGHT>{};

  std::iota(inputMat.begin(), inputMat.end(), 0.0f);
  std::fill(outputMat.begin(), outputMat.end(), 0.0f);

  inputMat.print();
  outputMat.print();

  // ...

  cppcon::benchmark([&]() { /* ... */ }, 100, "transpose");

  // ...

  inputMat.print();
  outputMat.print();

  REQUIRE(true);
}
