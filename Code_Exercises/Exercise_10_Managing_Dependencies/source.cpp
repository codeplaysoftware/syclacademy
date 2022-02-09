/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("managing_dependencies", "managing_dependencies_source") {
  constexpr size_t dataSize = 1024;

  int inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = static_cast<float>(i);
    inB[i] = static_cast<float>(i);
    inC[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  // Task: Run these kernels on the SYCL device, respecting the dependencies
  // as shown in the README

  // Kernel A
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = inA[i] * 2.0f;
  }

  // Kernel B
  for (int i = 0; i < dataSize; ++i) {
    inB[i] += inA[i];
  }

  // Kernel C
  for (int i = 0; i < dataSize; ++i) {
    inC[i] -= inA[i];
  }

  // Kernel D
  for (int i = 0; i < dataSize; ++i) {
    out[i] = inB[i] + inC[i];
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(out[i] == i * 2.0f);
  }
}
