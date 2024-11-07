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
 * // Declare a buffer using host ptr
 * auto buf = sycl::buffer{ptr, sycl::range{n},
 *                 {sycl::property::buffer::use_host_ptr{}}};
 *
 * // Declare a buffer relating to no host memory
 * auto buf = sycl::buffer{sycl::range{n}};
 *
 * // Set final data of a buffer
 * buf.set_final_data(host_ptr);
 *
 * // Set final data of a buffer to nullptr
 * buf.set_final_data(nullptr);
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
 * //    2. Enqueue a parallel for:
 *          cgh.parallel_for<class mykernel>(sycl::range{n}, [=](sycl::id<1> i)
 {
 *              // Do something
 *          });
 *
*/

#include <cassert>
#include <cstddef>

int main() {
  constexpr size_t dataSize = 1024;

  float in[dataSize], out[dataSize], tmp[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    in[i] = static_cast<float>(i);
    tmp[i] = 0.0f;
    out[i] = 0.0f;
  }

  // Task: run these kernels on a SYCL device, minimising the memory transfers
  // between the host and device

  // Kernel A
  for (int i = 0; i < dataSize; ++i) {
    tmp[i] = in[i] * 8.0f;
  }

  // Kernel B
  for (int i = 0; i < dataSize; ++i) {
    out[i] = tmp[i] / 2.0f;
  }

  for (int i = 0; i < dataSize; ++i) {
    assert(out[i] == i * 4.0f);
  }
}
