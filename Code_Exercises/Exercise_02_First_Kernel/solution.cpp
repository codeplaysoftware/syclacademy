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
 * free(ptr);
 *
 * // single task
 * auto event2 = q.single_task(global_range, {event1, event2}, lambda);
 *
 * Make sure to call `wait` or explicitly pass dependent events
 */

#include <iostream>

int main() {
  int a = 1, b = 2;

  // Construct a queue

  // Allocate memory for dev_a, dev_b

  // Multiply dev_a by 2. Use an in-kernel printf to check the result.

  // Multiply dev_b by 100. Use an in-kernel printf to check the result.

  // Add dev_a and dev_b together. What should the dependencies of this
  // single_task be?

  // Memcpy the result back to host. Print to stdout

  if (a == 202) {
    std::cout << "Got expected answer: 202\n";
  } else {
    std::cout << "Got unexpected answer: " << a << '\n';
  }
}
