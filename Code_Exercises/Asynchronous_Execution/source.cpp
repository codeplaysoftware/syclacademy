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
 * sycl::queue queue q = sycl::queue{};
 *
 * // Declare a buffer pointing to ptr
 * sycl::buffer buf = sycl::buffer{ptr, sycl::range{n}};
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
 *          accessor read_write_acc = sycl::accessor{buf, cgh};
 *          accessor read_acc = sycl::accessor{buf, cgh, sycl::read_only};
 *          accessor write_acc = sycl::accessor{buf, cgh, sycl::write_only};
 *          accessor no_init_acc = sycl::accessor{buf, cgh, sycl::no_init};
 * //    2. Enqueue a parallel for:
 *              cgh.parallel_for<class mykernel>(sycl::range{n},
 *                    [=](sycl::id<1> i) { // Do something });
 *
 *
*/

#include "../helpers.hpp"

void test_buffer() {
  // Use your code from the "Data Parallelism" exercise to start
  SYCLACADEMY_ASSERT_EQUAL(/*output data*/ 0, /*expected data*/ 0);
}

int main() { test_buffer(); }
