/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("usm_selector", "usm_selector_source") {

  // Task: create a queue to a device which supports USM allocations
  // Remember to check for exceptions
  auto usmQueue  = sycl::queue{};

  REQUIRE(true);
}
