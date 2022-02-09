/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("temporary_data", "temporary_data_source") {
  constexpr size_t dataSize = 1024;

  float in[dataSize], out[dataSize], tmp[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    in[i] = static_cast<float>(i);
    tmp[i] = 0.0f;
    out[i] = 0.0f;
  }

  // Task: run these kernels on a SYCL device, minimising the memory transfers between the host and device

  // Kernel A
  for (int i = 0; i < dataSize; ++i) {
    tmp[i] = in[i] * 8.0f;
  }


  // Kernel B
  for (int i = 0; i < dataSize; ++i) {
    out[i] = tmp[i] / 2.0f;
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 4.0f);
  }
}
