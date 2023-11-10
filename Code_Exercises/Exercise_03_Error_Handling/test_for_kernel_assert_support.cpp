// Copyright (C) 2023 Intel Corporation

// adapted from Figure 12-7 in book

// SPDX-License-Identifier: MIT

#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

// BEGIN CODE SNIP
template <typename queryT, typename T>
void do_query(const T& obj_to_query,
              const std::string& name, int indent = 4) {
  std::cout << std::string(indent, ' ') << name << " is '"
            << obj_to_query.template get_info<queryT>()
            << "'\n";
}

int main() {
  // Loop through the available platforms
  for (auto const& this_platform :
       platform::get_platforms()) {
    std::cout << "Found Platform:\n";
    do_query<info::platform::name>(this_platform,
                                   "info::platform::name");
    do_query<info::platform::vendor>(
        this_platform, "info::platform::vendor");
    do_query<info::platform::version>(
        this_platform, "info::platform::version");
    do_query<info::platform::profile>(
        this_platform, "info::platform::profile");

    // Loop through the devices available in this plaform
    for (auto& dev : this_platform.get_devices()) {
      std::cout << "  Device: "
                << dev.get_info<info::device::name>()
                << "\n";
      // is_cpu() == has(aspect::cpu)
      std::cout << "    is_cpu(): "
                << (dev.is_cpu() ? "Yes" : "No") << "\n";
      // is_cpu() == has(aspect::gpu)
      std::cout << "    is_gpu(): "
                << (dev.is_gpu() ? "Yes" : "No") << "\n";
      // is_cpu() == has(aspect::accelerator)
      std::cout << "    is_accelerator(): "
                << (dev.is_accelerator() ? "Yes" : "No")
                << "\n";

	std::cout << "    has(aspect::ext_oneapi_native_assert): "
                << (dev.has(aspect::ext_oneapi_native_assert) ? "Yes" : "No")
                << "\n";

#if 0
      std::cout << "    has(emulated): "
                << (dev.has(aspect::emulated) ? "Yes" : "No") << "\n";
      std::cout << "    has(fp16): "
                << (dev.has(aspect::fp16) ? "Yes" : "No")
                << "\n";
      std::cout << "    has(fp64): "
                << (dev.has(aspect::fp64) ? "Yes" : "No")
                << "\n";
      std::cout << "    has(host_debuggable): "
                << (dev.has(aspect::host_debuggable) ? "Yes"
                                                     : "No")
                << "\n";
      std::cout << "    has(atomic64): "
                << (dev.has(aspect::atomic64) ? "Yes"
                                              : "No")
                << "\n";
      // see Chapter 13
      std::cout << "    has(queue_profiling): "
                << (dev.has(aspect::queue_profiling) ? "Yes"
                                                     : "No")
                << "\n";
      std::cout << "    has(usm_device_allocations): "
                << (dev.has(aspect::usm_device_allocations)
                        ? "Yes"
                        : "No")
                << "\n";
      std::cout << "    has(usm_host_allocations): "
                << (dev.has(aspect::usm_host_allocations)
                        ? "Yes"
                        : "No")
                << "\n";
      std::cout << "    has(usm_atomic_host_allocations): "
                << (dev.has(
                        aspect::usm_atomic_host_allocations)
                        ? "Yes"
                        : "No")
                << "\n";
      std::cout << "    has(usm_shared_allocations): "
                << (dev.has(aspect::usm_shared_allocations)
                        ? "Yes"
                        : "No")
                << "\n";
      std::cout
          << "    has(usm_atomic_shared_allocations): "
          << (dev.has(aspect::usm_atomic_shared_allocations)
                  ? "Yes"
                  : "No")
          << "\n";
      std::cout << "    has(usm_system_allocations): "
                << (dev.has(aspect::usm_system_allocations)
                        ? "Yes"
                        : "No")
                << "\n";
#endif

      do_query<info::device::vendor>(
          dev, "info::device::vendor");
      do_query<info::device::driver_version>(
          dev, "info::device::driver_version");
#if 0
      do_query<info::device::max_work_item_dimensions>(
          dev, "info::device::max_work_item_dimensions");
      do_query<info::device::max_work_group_size>(
          dev, "info::device::max_work_group_size");
      do_query<info::device::mem_base_addr_align>(
          dev, "info::device::mem_base_addr_align");
      do_query<info::device::partition_max_sub_devices>(
          dev, "info::device::partition_max_sub_devices");

      std::cout << "    Many more queries are available "
                   "than shown here!\n";
#endif
    }
    std::cout << "\n";
  }
  return 0;
}
// END CODE SNIP

#if 0
// Some sample outputs:

Found Platform:
    info::platform::name is 'Intel(R) FPGA Emulation Platform for OpenCL(TM)'
    info::platform::vendor is 'Intel(R) Corporation'
    info::platform::version is 'OpenCL 1.2 Intel(R) FPGA SDK for OpenCL(TM), Version 20.3'
    info::platform::profile is 'EMBEDDED_PROFILE'
  Device: Intel(R) FPGA Emulation Device
    is_cpu(): No
    is_gpu(): No
    is_accelerator(): Yes
    has(fp16): No
    has(fp64): Yes
    has(atomic64): No
    has(queue_profiling): Yes
    has(usm_device_allocations): Yes
    has(usm_host_allocations): Yes
    has(usm_atomic_host_allocations): Yes
    has(usm_shared_allocations): Yes
    has(usm_atomic_shared_allocations): Yes
    has(usm_system_allocations): No
    info::device::vendor is 'Intel(R) Corporation'
    info::device::driver_version is '2023.15.3.0.20_160000'
    info::device::max_work_item_dimensions is '3'
    info::device::max_work_group_size is '67108864'
    info::device::mem_base_addr_align is '1024'
    info::device::partition_max_sub_devices is '8'
    Many more queries are available than shown here!

Found Platform:
    info::platform::name is 'Intel(R) OpenCL'
    info::platform::vendor is 'Intel(R) Corporation'
    info::platform::version is 'OpenCL 3.0 LINUX'
    info::platform::profile is 'FULL_PROFILE'
  Device: Intel(R) Core(TM) i7-8665U CPU @ 1.90GHz
    is_cpu(): Yes
    is_gpu(): No
    is_accelerator(): No
    has(fp16): No
    has(fp64): Yes
    has(atomic64): Yes
    has(queue_profiling): Yes
    has(usm_device_allocations): Yes
    has(usm_host_allocations): Yes
    has(usm_atomic_host_allocations): Yes
    has(usm_shared_allocations): Yes
    has(usm_atomic_shared_allocations): Yes
    has(usm_system_allocations): Yes
    info::device::vendor is 'Intel(R) Corporation'
    info::device::driver_version is '2023.15.3.0.20_160000'
    info::device::max_work_item_dimensions is '3'
    info::device::max_work_group_size is '8192'
    info::device::mem_base_addr_align is '1024'
    info::device::partition_max_sub_devices is '8'
    Many more queries are available than shown here!

=====
      
Found Platform:
    info::platform::name is 'Intel(R) OpenCL'
    info::platform::vendor is 'Intel(R) Corporation'
    info::platform::version is 'OpenCL 3.0 LINUX'
    info::platform::profile is 'FULL_PROFILE'
  Device: Intel(R) Xeon(R) E-2176G CPU @ 3.70GHz
    is_cpu(): Yes
    is_gpu(): No
    is_accelerator(): No
    has(fp16): No
    has(fp64): Yes
    has(atomic64): Yes
    has(queue_profiling): Yes
    has(usm_device_allocations): Yes
    has(usm_host_allocations): Yes
    has(usm_atomic_host_allocations): Yes
    has(usm_shared_allocations): Yes
    has(usm_atomic_shared_allocations): Yes
    has(usm_system_allocations): Yes
    info::device::vendor is 'Intel(R) Corporation'
    info::device::driver_version is '2023.15.3.0.20_160000'
    info::device::max_work_item_dimensions is '3'
    info::device::max_work_group_size is '8192'
    info::device::mem_base_addr_align is '1024'
    info::device::partition_max_sub_devices is '12'
    Many more queries are available than shown here!

Found Platform:
    info::platform::name is 'Intel(R) OpenCL HD Graphics'
    info::platform::vendor is 'Intel(R) Corporation'
    info::platform::version is 'OpenCL 3.0 '
    info::platform::profile is 'FULL_PROFILE'
  Device: Intel(R) UHD Graphics P630 [0x3e96]
    is_cpu(): No
    is_gpu(): Yes
    is_accelerator(): No
    has(fp16): Yes
    has(fp64): Yes
    has(atomic64): Yes
    has(queue_profiling): Yes
    has(usm_device_allocations): Yes
    has(usm_host_allocations): Yes
    has(usm_atomic_host_allocations): No
    has(usm_shared_allocations): Yes
    has(usm_atomic_shared_allocations): No
    has(usm_system_allocations): No
    info::device::vendor is 'Intel(R) Corporation'
    info::device::driver_version is '22.35.24055'
    info::device::max_work_item_dimensions is '3'
    info::device::max_work_group_size is '256'
    info::device::mem_base_addr_align is '1024'
    info::device::partition_max_sub_devices is '0'
    Many more queries are available than shown here!

Found Platform:
    info::platform::name is 'Intel(R) Level-Zero'
    info::platform::vendor is 'Intel(R) Corporation'
    info::platform::version is '1.3'
    info::platform::profile is 'FULL_PROFILE'
  Device: Intel(R) UHD Graphics P630 [0x3e96]
    is_cpu(): No
    is_gpu(): Yes
    is_accelerator(): No
    has(fp16): Yes
    has(fp64): Yes
    has(atomic64): Yes
    has(queue_profiling): Yes
    has(usm_device_allocations): Yes
    has(usm_host_allocations): Yes
    has(usm_atomic_host_allocations): No
    has(usm_shared_allocations): Yes
    has(usm_atomic_shared_allocations): No
    has(usm_system_allocations): No
    info::device::vendor is 'Intel(R) Corporation'
    info::device::driver_version is '1.3.24055'
    info::device::max_work_item_dimensions is '3'
    info::device::max_work_group_size is '256'
    info::device::mem_base_addr_align is '8'
    info::device::partition_max_sub_devices is '0'
    Many more queries are available than shown here!

#endif
