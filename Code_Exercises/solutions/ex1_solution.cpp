#include <CL/sycl.hpp>
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
