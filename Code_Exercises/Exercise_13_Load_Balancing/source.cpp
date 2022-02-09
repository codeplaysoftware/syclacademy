/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("load_balancing", "load_balancing_source") {
  constexpr size_t dataSize = 1024;
  constexpr float ratio = 0.5f;
  constexpr size_t dataSizeFirst = ratio * dataSize;
  constexpr size_t dataSizeSecond = dataSize - dataSizeFirst;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  // Task: split the total work across two distinct SYCL devices
  // You might split the work as in the two loops below.

  // Vector add for first part
  for (int i = 0; i < dataSizeFirst; ++i) {
    r[i] = a[i] + b[i];
  }

  // Vector add for second part
  for (int i = 0; i < dataSizeSecond; ++i) {
    r[dataSizeFirst + i] = a[dataSizeFirst + i] + b[dataSizeFirst + i];
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == static_cast<float>(i) * 2.0f);
  }
}
