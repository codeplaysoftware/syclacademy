/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CL/sycl.hpp>

class error_handling;

TEST_CASE("error_handling", "sycl_08_error_handling") {
   cl::sycl::default_selector device_selector;

   cl::sycl::queue queue(device_selector);
   {
     queue.submit([&] (cl::sycl::handler& cgh) {
       // here we use incorrect code to force an exception to be thrown
       auto range = cl::sycl::nd_range<1>(cl::sycl::range<1>(1), cl::sycl::range<1>(10));
       cgh.parallel_for<class error_handling>(range, [=] (cl::sycl::nd_item<1>) {});
     });
   }

  REQUIRE(true);
}