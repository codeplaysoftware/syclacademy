/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Declare a buffer pointing to ptr
 * auto buf = sycl::buffer{ptr, sycl::range{n}};
 *
 * // Do a USM malloc_device
 * auto ptr = sycl::malloc_device<T>(n, q);
 *
 * // Do a USM memcpy
 * q.memcpy(dst_ptr, src_ptr, sizeof(T)*n);
 *
 * // Wait on a queue
 * q.wait();
 *
 * // Submit work to the queue
 * q.submit([&](sycl::handler &cgh) {
 *   // COMMAND GROUP
 * });
 *
 *
 * // Within the command group you can
 * //    1. Declare an accessor to a buffer
 *          auto acc = sycl::accessor{buf, cgh};
 *          auto acc = sycl::accessor{buf, cgh, sycl::read_only};
 *          auto acc = sycl::accessor{buf, cgh, sycl::write_only};
 *          auto acc = sycl::accessor{buf, cgh, sycl::no_init};
 * //    2. Enqueue a parallel for:
 *              cgh.parallel_for<class mykernel>(sycl::range{n}, 
 *                    [=](sycl::id<1> i) { // Do something });
 *
 *
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("synchronization_usm", "synchronization_source") {
  // Use your code from Exercise 3 to start
  REQUIRE(true);
}

TEST_CASE("synchronization_buffer_acc", "synchronization_source") {
  // Use your code from Exercise 3 to start
  REQUIRE(true);
}
