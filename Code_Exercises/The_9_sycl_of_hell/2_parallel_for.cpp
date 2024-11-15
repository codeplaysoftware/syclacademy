#include "argparse.hpp"
#include <sycl/sycl.hpp>

#ifdef __ACPP__
void acpp_print(char* hello, size_t hello_size, size_t idx) {
    char buf[100] = {};
    strncpy(buf, hello, hello_size);
    auto [ptr, ec] = std::to_chars(buf+hello_size-1, buf+99, idx);
    strncpy(ptr, "\n", sizeof(1));
    sycl::detail::print(buf);
}
#endif

int main(int argc, char **argv) {

  //  _                ___
  // |_) _. ._ _  _     |  ._  ._     _|_
  // |  (_| | _> (/_   _|_ | | |_) |_| |_
  //                           |
  argparse::ArgumentParser program("2_parallel_for");

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
  //  _                        _
  // |_) _. ._ _. | |  _  |   |_ _  ._
  // |  (_| | (_| | | (/_ |   | (_) |

  sycl::queue Q;
  std::cout << "Running on "
            << Q.get_device().get_info<sycl::info::device::name>() << std::endl;

  // Similar to
  //   # pragma OMP PARALLEL FOR
  //   for(int idx=0; idx++; idx < global_range)
  Q.parallel_for(global_range, [=](sycl::id<1> idx) {
#ifdef __ACPP__
    char hello[] = "Hello, World! World rank ";
    acpp_print(hello, sizeof(hello), idx);
#else
    // Explicit cast because of printf shenaningan.
    sycl::ext::oneapi::experimental::printf("Hello, World! World rank %d\n",
                                            static_cast<int>(idx));
#endif
  });
  Q.wait();

  return 0;
}
