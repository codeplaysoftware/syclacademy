/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("nd_range_kernel", "nd_range_kernel_source") {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  // Task: parallelise the vector add kernel using nd_range
  for (int i = 0; i < dataSize; ++i) {
    r[i] = a[i] + b[i];
  }

  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(r[i] == i * 2);
  }
}
