#include <CL/sycl.hpp>
#include <iostream>

int main() {
  constexpr size_t dataSize = 1024;

  float a[dataSize], b[dataSize], r[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    r[i] = 0.0f;
  }

  // Task: Compute r[i] = a[i] + b[i] in parallel on the SYCL device
  //
  // Construct a queue
  auto q = sycl::queue{};

  // Allocate memory on device
  auto *devPtrA = sycl::malloc_device<float>(dataSize, q);
  auto *devPtrB = sycl::malloc_device<float>(dataSize, q);
  auto *devPtrR = sycl::malloc_device<float>(dataSize, q);

  // Copy memory to device
  auto e1 = q.memcpy(devPtrA, a, sizeof(float) * dataSize);
  auto e2 = q.memcpy(devPtrB, b, sizeof(float) * dataSize);

  // Use a parallel_for to add the two arrays
  q.parallel_for(sycl::range{dataSize}, {e1, e2}, [=](sycl::id<1> idx) {
     auto globalId = idx[0];
     devPtrR[globalId] = devPtrA[globalId] + devPtrB[globalId];
   }).wait();

  // Transfer memory back to device
  q.memcpy(r, devPtrR, sizeof(float) * dataSize).wait();

  // Check result
  bool correct_result = true;
  for (int i = 0; i < dataSize; ++i) {
    if (r[i] != static_cast<float>(i) * 2.0f) {
      std::cout << "r[i] != i * 2 for i = " << i << "\tr[i] = " << r[i] << '\n';
      correct_result = false;
    } 
  }

  if (correct_result) std::cout << "Correct result!\n";

  sycl::free(devPtrA, q);
  sycl::free(devPtrB, q);
  sycl::free(devPtrR, q);
}
