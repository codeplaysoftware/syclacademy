/*
 * This code performs a reduce operation over an array using a SYCL reduction
 * variable.
 *
 */

#include <benchmark.h>
#include <sycl/sycl.hpp>

using T = float;

constexpr size_t dataSize = 32'768;
constexpr size_t workGroupSize = 1024;
constexpr int numIters = 100;

int main(int argc, char *argv[]) {

  T a[dataSize];

  for (auto i = 0; i < dataSize; ++i) {
    a[i] = static_cast<T>(i);
  }

  auto q = sycl::queue{};

  T *devA = sycl::malloc_device<T>(dataSize, q);
  T *devReduced = sycl::malloc_device<T>(1, q); // Holds intermediate values

  T zeroVal = 0;
  auto e1 = q.memcpy(devA, a, sizeof(T) * dataSize);
  auto e2 = q.memcpy(devReduced, &zeroVal, sizeof(T));

  auto myNd = sycl::nd_range(sycl::range(dataSize), sycl::range(workGroupSize));

  util::benchmark(
      [&]() {
        q.submit([&](sycl::handler &cgh) {
           cgh.depends_on({e1, e2});
           auto myReduction = sycl::reduction(
               devReduced, sycl::plus<T>(),
               sycl::property::reduction::initialize_to_identity{});

           cgh.parallel_for(myNd, myReduction,
                            [=](sycl::nd_item<1> item, auto &sum) {
                              sum += devA[item.get_global_linear_id()];
                            });
         }).wait();
      },
      numIters, "Reduction using sycl::reduction");

  T devAns = 0;
  q.memcpy(&devAns, devReduced, sizeof(T)).wait();

  T serialAns = 0;
  for (auto i = 0; i < dataSize; i++) {
    serialAns += a[i];
  }

  std::cout << "Got device ans " << devAns << '\n';
  std::cout << "vs serial ans " << serialAns << "\n\n";

  sycl::free(devA, q);
  sycl::free(devReduced, q);
}
