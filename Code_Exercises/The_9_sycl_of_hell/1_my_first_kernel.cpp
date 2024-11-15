#include <sycl/sycl.hpp>

int main() {
  //         __                     ___
  //  /\    (_  o ._ _  ._  |  _     |  _.  _ |
  // /--\   __) | | | | |_) | (/_    | (_| _> |<
  //                    |

  // A "queue" is bound to a "device", and is used to submid work ("commands")
  // to the associated device.
  sycl::queue Q;
  std::cout << "Running on "
            << Q.get_device().get_info<sycl::info::device::name>() << "\n";

  // [=]: Capture the outside scope (variables) by value
  // (): Declaring an anonymouns function (lambda) without parameters
  // {...}: Body of the anonymouns function
  auto f = [=]() {
#ifdef __ACPP__
    sycl::detail::print("Hello, World for lambda!\n");
#else
    sycl::ext::oneapi::experimental::printf("Hello, World for lambda!\n");
#endif
  };
  // Submit one work item (a single task) to the GPU using the previous lambda
  // Queue submission are asyncrhonous (similar to OpenMP nowait)
  Q.single_task(f);
  // We wait for all the commands submited to the queue to complete
  // In this case only one
  Q.wait();
  return 0;
}
