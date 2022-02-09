/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("scalar_add", "scalar_add_source") {

  int a = 18, b = 24, r = 0;

  // Task: Compute a+b on the SYCL device
  r = a + b;


  REQUIRE(r == 42);
}
