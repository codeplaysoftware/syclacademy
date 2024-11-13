/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Get all available devices
 * auto devs = sycl::device::get_devices();
 *
 * // Construct a queue with a device
 * auto q = sycl::queue{my_device};
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
  constexpr float ratio = 0.5f;
  constexpr size_t dataSizeFirst = ratio * dataSize;
  constexpr size_t dataSizeSecond = dataSize - dataSizeFirst;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  // Task: split the total work across two distinct SYCL devices
  // You might split the work as in the two loops below.

  // Vector add for first part
  for (int i = 0; i < dataSizeFirst; ++i) {
    r[i] = a[i] + b[i];
  }

  // Vector add for second part
  for (int i = 0; i < dataSizeSecond; ++i) {
    r[dataSizeFirst + i] = a[dataSizeFirst + i] + b[dataSizeFirst + i];
  }

  for (int i = 0; i < dataSize; ++i) {
    SYCLACADEMY_ASSERT(r[i] == static_cast<float>(i) * 2.0f);
  }
}
