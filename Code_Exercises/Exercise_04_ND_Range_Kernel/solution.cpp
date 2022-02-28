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
 * // ND range
 * auto my_nd = nd_range(sycl::range(global_range), sycl::range(wkgroup_sz));
 *
 * // parallel_for
 * auto event2 = q.parallel_for(global_range, {event1, event2}, lambda);
 * auto event2 = q.parallel_for(my_nd, {event1, event2}, lambda);
 *
 * // Using q.submit to allocate local_memory
 * auto e = q.submit([&](sycl::handler &cgh){
 *   sycl::accessor<T, 1, sycl::access::mode::read_write,
 *                  sycl::access::target::local>
 *       local_mem(sycl::range<1>(workgroup_sz), cgh);
 *
 *     cgh.parallel_for( ... );
 *   });
 *
 * Make sure to call `wait` or explicitly pass dependent events
 */

#include <iostream>

template <typename T>
void flip_array(T *in_array, T *out_array, const size_t sz) {
  for (auto i = 0u; i < sz; i++) {
    out_array[i] = in_array[sz - 1 - i];
  }
}

template <typename T> void check_arrays(T *a, T *b, const size_t sz) {
  for (auto i = 0u; i < sz; i++) {
    if (a[i] != b[i])
      std::cout << "a[" << i << "] != b[" << i << "] "
                << "\na[i] = " << a[i] << "\tb[i] = " << b[i] << '\n';
  }
}

int main() {

  constexpr size_t dataSize = 16'384;

  float a[dataSize], result1[dataSize], result2[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<float>(i);
  }

  // Task
  // ~~~~~
  // Implement flip_array in a parallel_for using an nd_range

  // Construct a queue 

  // Allocate memory on device

  // Transfer memory to device

  // Use q.submit

  // Make a local accessor of size workgroup_sz

  // Use cgh.parallel_for to define a kernel with an nd_range

  // Within the kernel, load local memory with values from global memory.

  // Store the flipped array back into global memory

  // Memcpy back to host

  flip_array(a, result1, dataSize);

  // Check result
  check_arrays(result1, result2, dataSize);
}
