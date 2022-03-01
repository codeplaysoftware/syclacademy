#include <CL/sycl.hpp>
#include <iostream>

int main() {

  int a = 1, b = 2;
  // Construct a queue
  auto q = sycl::queue{};

  // Allocate memory for a_dev, b_dev
  auto a_dev = sycl::malloc_device<int>(1, q);
  auto b_dev = sycl::malloc_device<int>(1, q);

  // Copy memory onto the device
  auto e1 = q.memcpy(a_dev, &a, sizeof(int));
  auto e2 = q.memcpy(b_dev, &b, sizeof(int));

  // Multiply a_dev by 2.
  auto e3 = q.single_task(e1, [=] { (*a_dev) *= 2; });

  // Multiply b_dev by 100.
  auto e4 = q.single_task(e2, [=] { (*b_dev) *= 100; });

  // Add a_dev and b_dev together. What should the dependencies of this
  // single_task be?
  q.single_task({e3, e4}, [=] { a_dev[0] += b_dev[0]; }).wait();

  // Memcpy the result back to host. Print to stdout
  q.memcpy(&a, a_dev, sizeof(int)).wait();

  if (a == 202) {
    std::cout << "Got expected answer: 202\n";
  } else {
    std::cout << "Got unexpected answer: " << a << '\n';
  }
  
  // Free memory
  sycl::free(a_dev, q);
  sycl::free(b_dev, q);
}
