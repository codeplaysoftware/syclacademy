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
 *          auto read_write_acc = sycl::accessor{buf, cgh};
 *          auto read_acc = sycl::accessor{buf, cgh, sycl::read_only};
 *          auto write_acc = sycl::accessor{buf, cgh, sycl::write_only};
 *          auto no_init_acc = sycl::accessor{buf, cgh, sycl::no_init};
 * //    2. Enqueue a parallel for:
 * //             i: Without dependent events
 *                    cgh.parallel_for<class mykernel>(sycl::range{n},
 *                    [=](sycl::id<1> i) { // Do something });
 * //             ii: With dependent events
 *                    cgh.parallel_for<class mykernel>(sycl::range{n},
 *                    {event1, event2}, [=](sycl::id<1> i) {
 *                        // Do something
 *                      });
 *
*/

#include <cassert>
#include <cstddef>

int main() {
  constexpr size_t dataSize = 1024;

  int inA[dataSize], inB[dataSize], inC[dataSize], out[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = static_cast<float>(i);
    inB[i] = static_cast<float>(i);
    inC[i] = static_cast<float>(i);
    out[i] = 0.0f;
  }

  // Task: Run these kernels on the SYCL device, respecting the dependencies
  // as shown in the README

  // Kernel A
  for (int i = 0; i < dataSize; ++i) {
    inA[i] = inA[i] * 2.0f;
  }

  // Kernel B
  for (int i = 0; i < dataSize; ++i) {
    inB[i] += inA[i];
  }

  // Kernel C
  for (int i = 0; i < dataSize; ++i) {
    inC[i] -= inA[i];
  }

  // Kernel D
  for (int i = 0; i < dataSize; ++i) {
    out[i] = inB[i] + inC[i];
  }

  for (int i = 0; i < dataSize; ++i) {
    assert(out[i] == i * 2.0f);
  }
}
