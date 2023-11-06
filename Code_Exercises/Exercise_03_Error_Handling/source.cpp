/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("handling_errors", "handling_errors_source") {

  // Task: catch synchronous and asynchronous exceptions
  
  auto defaultQueue = sycl::queue{};

  auto buf = sycl::buffer<int>(sycl::range{1});

  defaultQueue.submit([&](sycl::handler& cgh) {
    // This throws an exception: an accessor has a range which is
    // outside the bounds of its buffer.
    auto acc = buf.get_access(cgh, sycl::range{2}, sycl::read_write);
  }).wait();

  defaultQueue.throw_asynchronous();

  REQUIRE(true);
}
