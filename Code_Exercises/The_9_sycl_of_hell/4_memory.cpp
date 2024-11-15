#include "argparse.hpp"
#include <sycl/sycl.hpp>

int main(int argc, char **argv) {

  //  _                ___
  // |_) _. ._ _  _     |  ._  ._     _|_
  // |  (_| | _> (/_   _|_ | | |_) |_| |_
  //                           |

  argparse::ArgumentParser program("4_memory");

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

  //            _           __
  // | | ._  o _|_ _   _|   (_  |_   _. ._ _   _|   ._ _   _  ._ _   _  ._
  // |_| | | |  | (/_ (_|   __) | | (_| | (/_ (_|   | | | (/_ | | | (_) | \/
  //                                                                      /

  sycl::queue Q;
  std::cout << "Running on "
            << Q.get_device().get_info<sycl::info::device::name>() << "\n";

  // Allocate 'managed' Memory. The memory is accessible by both the host and
  // the device
  int *A = sycl::malloc_shared<int>(global_range, Q);
  // Submit blocking kernel who use the memory
  Q.parallel_for(global_range, [=](auto id) { A[id] = id; });
  Q.wait();
  // Use Memory on the Host
  for (size_t i = 0; i < global_range; i++)
    std::cout << "A[ " << i << " ] = " << A[i] << std::endl;
  sycl::free(A, Q);
  return 0;
}
