/*
 * This code performs a reduce operation over an array using a SYCL reduction
 * variable.
 *
 */

#include <sycl/sycl.hpp>

#define MIN(a, b) a < b ? a : b

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;
constexpr size_t numWorkGroups = MIN(workGroupSize, dataSize / workGroupSize);

int main(int argc, char *argv[]) {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devA = sycl::malloc_device<T>(dataSize, q);
  T *devReduced = sycl::malloc_device<T>(1, q); // Holds intermediate values

  T zeroVal = 0;
  q.memcpy(devA, a, sizeof(T) * dataSize).wait();
  q.memcpy(devReduced, &zeroVal, sizeof(T)).wait();

  auto myNd =
      sycl::nd_range(sycl::range(numWorkGroups * workGroupSize), sycl::range(workGroupSize));

  q.submit([&](sycl::handler &cgh) {
     auto myReduction = sycl::reduction(devReduced, sycl::plus<>());

     cgh.parallel_for(myNd, myReduction, [=](sycl::nd_item<1> item, auto &sum) {
       sum += devA[item.get_global_linear_id()];
     });
   }).wait();

  T devAns = 0;
  q.memcpy(&devAns, devReduced, sizeof(T));

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << '\n';

  sycl::free(devA, q);
  sycl::free(devReduced, q);
}
