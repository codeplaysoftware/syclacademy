/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("hello_world", "hello_world_source") {

  // Print "Hello World!\n"
  std::cout << "Hello World!\n";

  // Task: Have this message print from the SYCL device instead of the host

  REQUIRE(true);
}
