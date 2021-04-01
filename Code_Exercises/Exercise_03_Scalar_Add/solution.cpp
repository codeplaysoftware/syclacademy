/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <SYCL/sycl.hpp>

class scalar_add;

TEST_CASE("scalar_add", "scalar_add_solution") {
  int a = 18, b = 24, r = 0;

  auto defaultQueue = sycl::queue{};

  {
    auto bufA = sycl::buffer{&a, sycl::range{1}};
    auto bufB = sycl::buffer{&b, sycl::range{1}};
    auto bufR = sycl::buffer{&r, sycl::range{1}};

    defaultQueue
        .submit([&](sycl::handler& cgh) {
          auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
          auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
          auto accR = bufR.get_access<sycl::access::mode::write>(cgh);

          cgh.single_task<scalar_add>([=]() { accR[0] = accA[0] + accB[0]; });
        })
        .wait();
  }

  REQUIRE(r == 42);
}
