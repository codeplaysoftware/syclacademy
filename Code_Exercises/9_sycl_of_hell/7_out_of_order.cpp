#include "argparse.hpp"
#include <sycl/sycl.hpp>

int main(int argc, char **argv) {

  //  _                ___
  // |_) _. ._ _  _     |  ._  ._     _|_
  // |  (_| | _> (/_   _|_ | | |_) |_| |_
  //                           |
  argparse::ArgumentParser program("7_out_of_order");

  program.add_argument("-g", "--global")
      .help("Global Range")
      .default_value(1)
      .action([](const std::string &value) { return std::stoi(value); });

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }

  const auto global_range = program.get<int>("-g");

  //    _                _    _
  //   / \    _|_    _ _|_   / \ ._ _|  _  ._
  //   \_/ |_| |_   (_) |    \_/ | (_| (/_ |
  //
  sycl::queue Q;
  std::cout << "Running on " << Q.get_device().get_info<sycl::info::device::name>() << "\n";

  // Allocate Device and Host Memory
  int *A = sycl::malloc_device<int>(global_range, Q);
  std::vector<int> A_host(global_range);

  // Submit non-blocking commands, chained by dependencies
  auto e = Q.parallel_for(global_range, [=](auto id) { A[id] = id; });
  // Copy will wait that `e` finished before starting executing
  // The command submission is still asynchronous
  Q.copy(A, A_host.data(), global_range, e).wait();
  sycl::free(A, Q);

  for (size_t i = 0; i < global_range; i++)
    std::cout << "A_host[ " << i << " ] = " << A_host[i] << std::endl;
  return 0;
}
