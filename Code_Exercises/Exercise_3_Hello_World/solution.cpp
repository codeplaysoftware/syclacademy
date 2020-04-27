/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CL/sycl.hpp>

class hello_world;

TEST_CASE("hello_world", "sycl_03_hello_world") {
  cl::sycl::default_selector selector;

  cl::sycl::queue myQueue(selector);
  std::cout << "Running on "
    << myQueue.get_device().get_info<cl::sycl::info::device::name>()
    << "\n";

  myQueue.submit([&](cl::sycl::handler& cgh) {
    cl::sycl::stream os(1024, 80, cgh);

    cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
    });

  myQueue.wait();

  REQUIRE(true);
}

class print_ids;

TEST_CASE("print_ids", "sycl_03_hello_world") {
  cl::sycl::default_selector selector;

  cl::sycl::queue myQueue(selector);
  std::cout << "Running on "
    << myQueue.get_device().get_info<cl::sycl::info::device::name>()
    << "\n";

  myQueue.submit([&](cl::sycl::handler& cgh) {
    cl::sycl::stream os(1024, 80, cgh);

    cgh.parallel_for<print_ids>(cl::sycl::range<1>(1024),
      [=](cl::sycl::id<1> idx) {
        if (idx[0] == 999) {
          os << "I am on " << idx << "\n";
        }
      });
    });

  myQueue.wait();

  REQUIRE(true);
}

