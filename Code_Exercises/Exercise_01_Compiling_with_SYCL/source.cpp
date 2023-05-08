/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <sycl/sycl.hpp>
#include <iostream>

int main() {
  // Construct a queue
  auto q = sycl::queue{};

  // Get the device associated with queue
  auto d = q.get_device();

  // Print the device name to stdout
  auto dev_name = d.get_info<sycl::info::device::name>();

  std::cout << "Chosen device: " << dev_name << std::endl;
}
