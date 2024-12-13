/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <sycl/sycl.hpp>

#include "../helpers.hpp"

int usm_selector(const sycl::device& dev) {
  if (dev.has(sycl::aspect::usm_device_allocations)) {
    return 1;
  }
  return -1;
}

int main() {
  try {
    auto usmQueue = sycl::queue{usm_selector};

    usmQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  SYCLACADEMY_ASSERT(true);
}
