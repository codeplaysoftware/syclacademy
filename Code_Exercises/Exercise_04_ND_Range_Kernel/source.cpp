/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

/*
 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Include SYCL header
 * #include <sycl/sycl.hpp>
 *
 * // Construct a queue
 * auto q = sycl::queue{};
 *
 * // Make a buffer associated with `a`
 * auto buf = sycl::buffer{&a, sycl::range<1>{1}}
 *
 * // Submit a task to the queue
 * q.submit([&](sycl::handler &cgh) {
 *
 *   // Declaring different accessors
 *   auto read_acc = sycl::accessor{buf, cgh, sycl::read_only};
 *   auto write_acc = sycl::accessor{buf, cgh, sycl::write_only};
 *   auto read_write_acc = sycl::accessor{buf, cgh};
 *
 *   // submit a parallel_for with an nd_range
 *   cgh.parallel_for(sycl::nd_range{sycl::range{global_range},
 *      sycl::range{local_range}}, [=](sycl::nd_item my_nd_it){
 *      // do stuff
 *   });
 *
 * });
 *
 * // N.B. - Each call to q.submit can only contain a single command
 * (parallel_for)
 *
 * // N.B. - Buffers will only update the memory they point to when they are
 * // destroyed
 *
 */

#include <stddef.h> // replace both headers with sycl/sycl.hpp
#include <cassert>

int main() {
  constexpr size_t dataSize = 1024;

  int a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = i;
    b[i] = i;
    r[i] = 0;
  }

  // Task: parallelise the vector add kernel using nd_range
  for (int i = 0; i < dataSize; ++i) {
    r[i] = a[i] + b[i];
  }

  for (int i = 0; i < dataSize; ++i) {
    assert(r[i] == i * 2);
  }
}
