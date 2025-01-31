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
 * // Submit work to the queue
 * q.submit([&](sycl::handler &cgh) {
 *   // COMMAND GROUP
 * });
 *
 * // Within the command group you can
 * //    1. Declare an accessor to a buffer
 *          auto read_write_acc = sycl::accessor{buf, cgh};
 *          auto read_acc = sycl::accessor{buf, cgh, sycl::read_only};
 *          auto write_acc = sycl::accessor{buf, cgh, sycl::write_only};
 *          auto no_init_acc = sycl::accessor{buf, cgh, sycl::no_init};
 * //    2. Enqueue a single task:
 *          cgh.single_task<class mykernel>([=]() {
 *              // Do something
 *          });
 * //    3. Enqueue a parallel for:
 *          cgh.parallel_for<class mykernel>(sycl::range{n}, [=](sycl::id<1> i)
 {
 *              // Do something
 *          });
 *
*/

#include "../helpers.hpp"

int main() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  // Task: Compute r[i] = a[i] + b[i] in parallel on the SYCL device
  for (int i = 0; i < dataSize; ++i) {
    r[i] = a[i] + b[i];
  }

  SYCLACADEMY_ASSERT_EQUAL(r, [](size_t i) { return i * 2; });
}
