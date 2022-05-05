/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

// Copyright (C) Codeplay Software Limited

/*
 * SYCL Quick Reference
 * ~~~~~~~~~~~~~~~~~~~~
 * Buffers
 * // Include SYCL header
 * #include <CL/sycl.hpp>
 *
 * // Default construct a queue
 * auto q = sycl::queue{};
 *
 * // Make a buffer associated with `a`
 * auto buf = sycl::buffer{&a, sycl::range<1>{1}}
 *
 * // Submit a task to the queue
 * q.submit([&](sycl::handler &cgh) {
 *   
 *   // Declaring different accessors
 *   sycl::accessor read_acc{buf, cgh, sycl::read_only};
 *   sycl::accessor write_acc{buf, cgh, sycl::write_only};
 *   sycl::accessor read_write_acc{buf, cgh, sycl::read_write};
 *
 *   // submit a single task
 *   cgh.single_task([=](){
 *      // do stuff      
 *   });
 *
 * });
 *
 * // N.B. - Each call to q.submit can only contain a single command (single_task)
 *
 * // N.B. - Buffers will only update the memory they point to when they are 
 * // destroyed
 * 
 * USM
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

 *
 */

#include <iostream>

using T = int;

constexpr T fill_val = 31;

int main() {
  
  // Use Buffers
  int a = 1, b = 2;

  // 1. Construct a queue

  // 2. Make a buffer for a and another for b

  // 3. Use q.submit to add a and b and store the value in a. 
  
  // Use braces around steps 2-5 so that memory is updated when buffers go out
  // of scope


  if (a == 202) {
    std::cout << "Got expected answer: 202\n";
  } else {
    std::cout << "Got unexpected answer: " << a << '\n';
  }

  // Use USM
  int a = 0;

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


