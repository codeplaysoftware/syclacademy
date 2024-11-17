/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

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
  for (int i = 0; i < dataSize; ++i) {
    REQUIRE(result[i] == i * 2);
  }
}

// Helper function: To run a vector-add
void vector_add(sycl::queue& q, int* result, size_t dataSize) {

  // STEP1: allocate memory on the host
  auto host_ptrA = new int[dataSize];
  auto host_ptrB = new int[dataSize];

  // STEP1: allocate memory on the device
  auto dev_ptrA = sycl::malloc_device<int>(dataSize, q);
  auto dev_ptrB = sycl::malloc_device<int>(dataSize, q);
  auto dev_ptrR = sycl::malloc_device<int>(dataSize, q);

  // STEP1: Initialize the host arrays (host_ptrA, host_ptrB)
  for (int i = 0; i < dataSize; ++i) {
    host_ptrA[i] = i;
    host_ptrB[i] = i;
  }

  // STEP2: Copy the input-data from host to device
  q.memcpy(dev_ptrA, host_ptrA, sizeof(int) * dataSize);
  q.memcpy(dev_ptrB, host_ptrB, sizeof(int) * dataSize);
  q.wait(); // wait for the copy to finish before launching the kernel

  // STEP3: Launch the SYCL kernel
  q.parallel_for(sycl::range{dataSize}, [=](sycl::item<1> itm) {
    auto globalId = itm.get_id();
    dev_ptrR[globalId] = dev_ptrA[globalId] + dev_ptrB[globalId];
  }).wait();

  // STEP4: Copy the results back to host from device
  q.memcpy(result, dev_ptrR, sizeof(int) * dataSize);
  q.wait();

  // STEP5: Free the memory
  delete[] host_ptrA;
  delete[] host_ptrB;

  sycl::free(dev_ptrA, q);
  sycl::free(dev_ptrB, q);
  sycl::free(dev_ptrR, q);
}

// Case 1: Simple test to set up a SYCL queue
// - Creates a SYCL queue
// - Print info on the device associated with SYCL queue
// - Runs a Hello World kernel
int main () {
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


// Case 2: Complex test to run the same kernel on both CPU and GPU
// - Creates a SYCL queue (targetting CPU-device), print info on the device associated with SYCL queue
// - Runs a `vector_add` kernel on the device
// - Verifies the results from the above kernel run with a reference value
// - TODO: repeat the above steps for GPU

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


  // Creates a SYCL queue targetting GPU-device
  sycl::platform gpu_plt(sycl::gpu_selector_v);
  auto gpu_devices = gpu_plt.get_devices();
  std::cout << "Number of GPU devices: " << gpu_devices.size() << std::endl;
  print_device_info(gpu_devices);
  auto gpu_q = sycl::queue{gpu_devices[0]};

  // `gpu_result` is a array to store the results and verify them later for correctness
  int* gpu_result = new int[dataSize];
  vector_add(gpu_q, gpu_result, dataSize); // kernel call
  verify_results(gpu_result, dataSize);
  delete[] gpu_result;
}
