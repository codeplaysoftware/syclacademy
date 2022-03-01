/*
 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * // Include SYCL header
 * #include <CL/sycl.hpp>
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Allocate device memory
 * auto * devPtr = malloc_device<T>(mycount, q);
 *
 * // Memcpy
 * auto event1 = q.memcpy(dst, src, sizeof(T)*n, {dep_event1, dep_event2});
 *
 * // Free memory
 * sycl::free(ptr, q);
 *
 * // parallel_for
 * auto event2 = q.parallel_for(global_range, {event1, event2}, lambda);
 *
 * Make sure to call `wait` or explicitly pass dependent events
 */

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

  // Construct a queue

  // Allocate memory on device

  // Copy memory to device

  // Use a parallel_for to add the two arrays

  // Transfer memory back to device

  // Check result
  bool correct_result = true;
  for (int i = 0; i < dataSize; ++i) {
    if (r[i] != static_cast<float>(i) * 2.0f) {
      std::cout << "r[i] != i * 2 for i = " << i << "\tr[i] = " << r[i] << '\n';
      correct_result = false;
    }
  }
  if (correct_result) std::cout << "Got correct result!\n";
}
