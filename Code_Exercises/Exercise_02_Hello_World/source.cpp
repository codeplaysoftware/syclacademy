/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 *
 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Include SYCL header
 * #if __has_include(<SYCL/sycl.hpp>)
 * #include <SYCL/sycl.hpp>
 * #else
 * #include <CL/sycl.hpp>
 * #endif
 *
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Submit work to the queue
 * q.submit([&](sycl::handler &cgh) {
 *   // COMMAND GROUP
 * });
 *
 * // Within the command group you can
 * //    1. Enqueue a command:
 *          cgh.single_task<class mykernel>([=]() {
 *              // Do something
 *          });
 *
 *       2. Declare a sycl::stream for printing from device:
 *          auto os = sycl::stream{buf_size, wi_size, cgh};
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("hello_world", "hello_world_source") {

  // Print "Hello World!\n"
  std::cout << "Hello World!\n";

  // Task: Have this message print from the SYCL device instead of the host

  REQUIRE(true);
}
