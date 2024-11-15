/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <sycl/sycl.hpp>

// Helper function: To print information on the devices found
void print_device_info(std::vector<sycl::device>& devs) {
  // Loop through the vector of SYCL devices
  int devID = 0;
  for (auto dev : devs) {
    std::cout << "Found [" << devID << "]: "
              << dev.get_info<sycl::info::device::name>() << ", "
              << "\t" << "Driver version: " << dev.get_info<sycl::info::device::driver_version>()  << ", "
              << "\t" << "Device version: " << dev.get_info<sycl::info::device::version>()
              << "\n";
    devID++;
  }
}

// Helper function: To verify the results of an array `result` with a reference value
void verify_results(int* result, size_t dataSize) {
  // for (int i = 0; i < dataSize; ++i) {
  //   REQUIRE(result[i] == i * 2);
  // }
}

// Helper function: To run a vector-add
void vector_add(sycl::queue& q, int* result, size_t dataSize) {

  // [TODO] STEP1: allocate memory on the host
  // auto host_ptrA =
  // auto host_ptrB =

  // [TODO] STEP1: allocate memory on the device
  // auto dev_ptrA =
  // auto dev_ptrB =
  // auto dev_ptrR =

  // (uncomment) STEP1: Initialize the host arrays (host_ptrA, host_ptrB)
  // for (int i = 0; i < dataSize; ++i) {
  //   host_ptrA[i] = i;
  //   host_ptrB[i] = i;
  // }

  // [TODO] STEP2: Copy the input-data from host to device

  // (uncomment) STEP3: Launch the SYCL kernel
  // q.parallel_for(sycl::range{dataSize}, [=](sycl::item<1> itm) {
  //   auto globalId = itm.get_id();
  //   dev_ptrR[globalId] = dev_ptrA[globalId] + dev_ptrB[globalId];
  // }).wait();

  // [TODO] STEP4: Copy the results back to host from device

  // [TODO] STEP5: Free the memory

}

// Case 1: Simple test to set up a SYCL queue
// - Creates a SYCL queue
// - Print info on the device associated with SYCL queue
// - Runs a Hello World kernel
TEST_CASE("queue_query", "queue_query") {
  // select a default device and construct a queue
  sycl::platform plt;
  auto devices = plt.get_devices();
  print_device_info(devices);
  auto q = sycl::queue{devices[0]};

  q.submit([&](sycl::handler& cg) {
    auto os = sycl::stream{1024, 1024, cg};
    cg.parallel_for(10, [=](sycl::id<1> myid)
    {
      os << "Hello World! My ID is " << myid << "\n";
    });

  });
  q.wait();
}

// Case 2: Complex test to run the same kernel on both CPU and GPU
// - Creates a SYCL queue (targetting CPU-device), print info on the device associated with SYCL queue
// - Runs a `vector_add` kernel on the device
// - Verifies the results from the above kernel run with a reference value
// - TODO: repeat the above steps for GPU
TEST_CASE("multi_arch", "multi_arch") {

  // Size of the array for the upcoming kernel
  constexpr size_t dataSize = 1<<10;

  // Creates a SYCL queue targetting CPU-device
  sycl::platform cpu_plt(sycl::cpu_selector_v);
  auto cpu_devices = cpu_plt.get_devices();
  std::cout << "Number of CPU devices: " << cpu_devices.size() << std::endl;
  print_device_info(cpu_devices);
  auto cpu_q = sycl::queue{cpu_devices[0]};

  // `cpu_result` is a array to store the results and verify them later for correctness
  int* cpu_result = new int[dataSize];
  vector_add(cpu_q, cpu_result, dataSize); // kernel call
  verify_results(cpu_result, dataSize);
  delete[] cpu_result;

  // TODO: Run the above vector-add function for GPU device
}
