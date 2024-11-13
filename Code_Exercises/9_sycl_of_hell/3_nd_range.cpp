#include "argparse.hpp"
#include <sycl/sycl.hpp>

int main(int argc, char **argv) {

  //  _                ___
  // |_) _. ._ _  _     |  ._  ._     _|_
  // |  (_| | _> (/_   _|_ | | |_) |_| |_
  //
  argparse::ArgumentParser program("3_nd_range");

  program.add_argument("-g", "--global")
      .help("Global Range")
      .default_value(1)
      .action([](const std::string &value) { return std::stoi(value); });

  program.add_argument("-l", "--local")
      .help("Local Range")
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
  const auto local_range = program.get<int>("-l");

  // ._   _|        ._ _. ._   _   _
  // | | (_|        | (_| | | (_| (/_
  //           __              _|

  sycl::queue Q;
  std::cout << "Running on " << Q.get_device().get_info<sycl::info::device::name>() << std::endl;

  // nd_range, generate a nd_item who allow use to query
  // loop dispach information
  Q.parallel_for(sycl::nd_range<1>{global_range, local_range}, [=](sycl::nd_item<1> idx) {
     const int world_rank = idx.get_global_id(0);
     const int work_size = idx.get_global_range(0);
     const int local_rank = idx.get_local_id(0);
     const int local_size = idx.get_local_range(0);
     const int group_rank = idx.get_group(0);
     const int group_size = idx.get_group_range(0);

     sycl::ext::oneapi::experimental::printf(
         "Hello, World! World rank/size: %d/%d | Local rank/size: %d/%d | Group "
         "rank/size: %d/%d\n",
         world_rank, work_size, local_rank, local_size, group_rank, group_size);
   }).wait(); // End of the queue commands

  return 0;
}
