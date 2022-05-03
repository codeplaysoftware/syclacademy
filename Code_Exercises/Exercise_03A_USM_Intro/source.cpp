// Copyright (C) Codeplay Software Limited

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
 * auto * devPtr = malloc_device<int>(mycount, q);
 *
 * // Fill ptr with value
 * q.fill(devPtr, value, num_items);
 *
 * // Memcpy
 * auto event1 = q.memcpy(dst, src, sizeof(T)*n);
 * // (dst and src are pointers)
 *
 * // Free memory
 * sycl::free(ptr, q);
 *
 */

#include <iostream>

using T = int;

constexpr T fill_val = 31;

int main() {

  int a = 0;

  // Construct a queue

  // Allocate memory at devPtr for one T on device

  // Fill the memory at devPtr with fill_val

  // Memcpy the value at devPtr back into a
  
  // Free the memory at devPtr

  if (a == fill_val) {
    std::cout << "Got expected answer: " << fill_val << '\n';
  } else {
    std::cout << "Got unexpected answer: " << a << '\n';
  }
}

