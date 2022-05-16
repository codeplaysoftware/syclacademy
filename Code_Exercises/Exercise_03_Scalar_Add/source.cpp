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
  // values to add
  int a = 18, b = 24, r = 0;
  
  // set up the default queue
  auto defaultQueue = sycl::queue{};
  // set up the scope for the buffers
  {
  defaultQueue
        .submit([&](sycl::handler &cgh) {
          // set up the buffer accessors 
          // e.g. auto accA = sycl::accessor{bufA, cgh, sycl::read_only};

          // write the single_task kernel for the addition
          // e.g. cgh.single_task<scalar_add>([=] { accR[0] = accA[0] + accB[0]; });
        })
        .wait();
  
  // when the buffers move out of scope they are destroyed
  }
  REQUIRE(r == 42);
}
