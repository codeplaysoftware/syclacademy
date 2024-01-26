/*

Licensed under a Creative Commons Attribution-ShareAlike 4.0
International License.

Code by James Reinders.

*/

#include <sycl/sycl.hpp>

int main(int argc, char* argv[]) {

  sycl::queue q;

  std::cout << "Running on "
	    << q.get_device().get_info<sycl::info::device::name>();

  q.submit([&](sycl::handler& cgh3) {
	     auto os = sycl::stream{128, 128, cgh3};
	     cgh3.single_task(
			      [=]() { os << "\nHello World!\n"; });
	   });
}
