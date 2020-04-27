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

struct gpu_selector : public cl::sycl::device_selector {
  int operator()(const cl::sycl::device& d) const override {
    if (d.is_gpu()) {
      return 1;
    } else {
      return -1;
    }
  }
};

TEST_CASE("default_selector", "sycl_02_configuring_a_queue") {
  try {
    cl::sycl::queue defaultQueue;

    std::cout
        << "Default selector chose: "
        << defaultQueue.get_device().get_info<cl::sycl::info::device::name>()
        << "\n";

  } catch (...) {
    std::cout << "No device could be found\n";
  }

  REQUIRE(true);
}

TEST_CASE("gpu_selector", "sycl_02_configuring_a_queue") {
  try {
    cl::sycl::queue gpuQueue(gpu_selector{});

    std::cout << "GPU selector chose: "
              << gpuQueue.get_device().get_info<cl::sycl::info::device::name>()
              << "\n";

  } catch (...) {
    std::cout << "No GPU could be found\n";
  }

  REQUIRE(true);
}

TEST_CASE("print_info", "sycl_02_configuring_a_queue") {
  try {
    cl::sycl::queue defaultQueue;

    auto dev = defaultQueue.get_device();

    std::cout << "Device name         : "
              << dev.get_info<cl::sycl::info::device::name>() << "\n";
    std::cout << "Vendor name         : "
              << dev.get_info<cl::sycl::info::device::vendor>() << "\n";
    std::cout << "Driver version      : "
              << dev.get_info<cl::sycl::info::device::driver_version>() << "\n";
    std::cout << "Address bits        : "
              << dev.get_info<cl::sycl::info::device::address_bits>() << "\n";
    std::cout << "Max work-group size : "
              << dev.get_info<cl::sycl::info::device::max_work_group_size>()
              << "\n";

  } catch (...) {
    std::cout << "No device could be found\n";
  }

  REQUIRE(true);
}
