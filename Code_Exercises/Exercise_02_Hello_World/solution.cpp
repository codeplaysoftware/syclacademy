/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <CL/sycl.hpp>
class hello_world;

int main() {
  // Construct a queue
  auto q = sycl::queue{};

  q.submit([&](sycl::handler& cgh) {
        auto os = sycl::stream{128, 128, cgh};

        cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
      }).wait();
	  
  return 1;
}
