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
  int a = 18, b = 24, r = 0;

  // Set up the asynchronous exception handler code
  // This is a try catch around the main body of code below
  // but also includes a loop to iterate the exceptions (see slide 8)

    // here is an existing kernel to add some values together
    auto defaultQueue = sycl::queue{asyncHandler};

    {
      auto bufA = sycl::buffer{&a, sycl::range{1}};
      auto bufB = sycl::buffer{&b, sycl::range{1}};
      auto bufR = sycl::buffer{&r, sycl::range{1}};

      defaultQueue
          .submit([&](sycl::handler& cgh) {
            auto accA = sycl::accessor{bufA, cgh, sycl::read_only};
            auto accB = sycl::accessor{bufB, cgh, sycl::read_only};
            auto accR = sycl::accessor{bufR, cgh, sycl::write_only};

            cgh.single_task<scalar_add>([=]() { accR[0] = accA[0] + accB[0]; });
          })
          .wait();
    }

    // using the default queue throw an asynchronous exception
    // e.g. defaultQueue.throw_asynchronous();

  // and the catch part of the try goes next (see slide 9)
  
  REQUIRE(r == 42);
}
