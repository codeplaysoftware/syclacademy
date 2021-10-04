/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if __has_include(<SYCL/sycl.hpp>)
#include <SYCL/sycl.hpp>
#else
#include <CL/sycl.hpp>
#endif

class hello_world;

TEST_CASE("hello_world", "hello_world_solution") {
  auto defaultQueue = sycl::queue{};

  defaultQueue
      .submit([&](sycl::handler& cgh) {
        auto os = sycl::stream{128, 128, cgh};

        cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
      })
      .wait();

  REQUIRE(true);
}
