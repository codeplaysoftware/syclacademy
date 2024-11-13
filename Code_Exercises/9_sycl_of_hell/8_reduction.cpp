#include "argparse.hpp"
#include <sycl/sycl.hpp>

int main(int argc, char **argv) {

  //  _                ___
  // |_) _. ._ _  _     |  ._  ._     _|_
  // |  (_| | _> (/_   _|_ | | |_) |_| |_
  //                           |

  argparse::ArgumentParser program("8_reduction");

  program.add_argument("-g", "--global")
      .help("Global Range")
      .default_value(1)
      .action([](const std::string &value) { return std::stoi(value); });

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cout << program;
    std::exit(1);
  }

  const auto global_range = program.get<int>("-g");

  //    _
  //   |_)  _   _|      _ _|_ o  _  ._
  //   | \ (/_ (_| |_| (_  |_ | (_) | |
  //
  sycl::queue Q;
  std::cout << "Running on " << Q.get_device().get_info<sycl::info::device::name>() << "\n";

  // Allocate Memory to store the reduction
  int *s = sycl::malloc_shared<int>(1, Q);
  // Submit reduction kernel
  Q.parallel_for(global_range, sycl::reduction(s, sycl::plus<int>()), [=](auto id, auto &sum) {
     sum += static_cast<int>(id);
   }).wait();

  int s_expected = global_range * (global_range - 1) / 2;

  std::cout << "Expected sum: " << s_expected << " | Computed sum: " << *s << std::endl;
  return s_expected != *s;
}
