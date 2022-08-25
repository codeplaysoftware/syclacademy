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
 * // Construct an in-order queue
 * auto q = sycl::queue{sycl::default_selector{}, 
 *        {sycl::property::queue::in_order{}}};
 *
 * // Declare a buffer pointing to ptr
 * auto buf = sycl::buffer{ptr, sycl::range{n}};
 *
 * // Do a USM memcpy
 * auto event = q.memcpy(dst_ptr, src_ptr, sizeof(T)*n);
 * // Do a USM memcpy with dependent events
 * auto event = q.memcpy(dst_ptr, src_ptr, sizeof(T)*n, {event1, event2});
 *
 * // Wait on an event
 * event.wait();
 *
 * // Wait on a queue
 * q.wait();
 *
 * // Submit work to the queue
 * auto event = q.submit([&](sycl::handler &cgh) {
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
 * //             i: Without dependent events
 *                    cgh.parallel_for<class mykernel>(sycl::range{n}, 
 *                    [=](sycl::id<1> i) { // Do something });
 * //             ii: With dependent events
 *                    cgh.parallel_for<class mykernel>(sycl::range{n}, 
 *                    {event1, event2}, [=](sycl::id<1> i) { 
 *                        // Do something
 *                      });

*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("in_order_queue", "in_order_queue_source") {
  // Use the Exercise 10 solution to start
  REQUIRE(true);
}
