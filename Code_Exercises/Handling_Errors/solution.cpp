/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include "../helpers.hpp"

#include <sycl/sycl.hpp>

int main() {
  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto &e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    auto defaultQueue = sycl::queue{asyncHandler};

    auto buf = sycl::buffer<int>(sycl::range{1});

    defaultQueue.submit([&](sycl::handler &cgh) {
      // This throws an exception: an accessor has a range which is
      // outside the bounds of its buffer.
      auto acc = buf.get_access(cgh, sycl::range{2}, sycl::read_write);
    });
    defaultQueue.wait_and_throw();
  } catch (const sycl::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  SYCLACADEMY_ASSERT(true);
}
