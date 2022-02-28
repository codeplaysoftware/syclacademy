#include <CL/sycl.hpp>
#include <iostream>

constexpr size_t dataSize = 16'384;
constexpr size_t wkgrp_sz = 32;

template <typename T>
void flip_array(T *in_array, T *out_array, const size_t sz) {
  for (auto i = 0u; i < sz; i++) {
    out_array[i] = in_array[sz - 1 - i];
  }
}

template <typename T> void check_arrays(T *a, T *b, const size_t sz) {
  bool no_errors = true;
  for (auto i = 0u; i < sz; i++) {
    if (a[i] != b[i]) {
      std::cout << "a[" << i << "] != b[" << i << "] "
                << "\na[i] = " << a[i] << "\tb[i] = " << b[i] << '\n';
      no_errors = false;
    }
  }
  if (no_errors)
    std::cout << "Flip completed successfully!\n";
}

using T = float;

int main() {

  T a[dataSize], serial_flipped[dataSize], dev_flipped[dataSize];
  for (int i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  // Allocate memory on device
  auto q = sycl::queue{};

  auto my_nd = sycl::nd_range(sycl::range(dataSize), sycl::range(wkgrp_sz));

  T *devPtrA = sycl::malloc_device<T>(dataSize, q);
  T *devPtrB = sycl::malloc_device<T>(dataSize, q);

  q.memcpy(devPtrA, a, sizeof(T) * dataSize).wait();

  q.submit([&](sycl::handler &cgh) {
     sycl::accessor<T, 1, sycl::access::mode::read_write,
                    sycl::access::target::local>
         local_mem(sycl::range<1>(wkgrp_sz), cgh);

     cgh.parallel_for(my_nd, [=](sycl::nd_item<1> item) {
       auto localIdx = item.get_local_linear_id();
       auto globalIdx = item.get_global_linear_id();
       auto groupIdx = item.get_group_linear_id();
       auto num_groups = item.get_group_range(0);

       local_mem[localIdx] = devPtrA[globalIdx];
       item.barrier();
       devPtrB[(num_groups - groupIdx - 1) * wkgrp_sz + localIdx] =
           local_mem[wkgrp_sz - localIdx - 1];
     });
   }).wait();

  q.memcpy(dev_flipped, devPtrB, sizeof(T) * dataSize).wait();

  flip_array(a, serial_flipped, dataSize);

  // Check result
  check_arrays(serial_flipped, dev_flipped, dataSize);

  sycl::free(devPtrA, q);
  sycl::free(devPtrB, q);
}
