#include <sycl/sycl.hpp>

int main() {
  //         __                     ___
  //  /\    (_  o ._ _  ._  |  _     |  _.  _ |
  // /--\   __) | | | | |_) | (/_    | (_| _> |<
  //                    |

  // "stream" associated to Device used to submit assychrnous "job" to the device
  sycl::queue Q;
  std::cout << "Running on " << Q.get_device().get_info<sycl::info::device::name>() << "\n";

  // Submit one work item (a single task) to the GPU using a lambda
  // Queue submission are asyncrhonous (similar to OpenMP nowait)
 
  /*
  struct PrintKernel
  {
    // Overload `()` operator
    // Single task assume no argument
    void operator()() const
    {
	sycl::ext::oneapi::experimental::printf("Hello, World!\n");
        //return value + 1;
    }
  };
  Q.single_task(PrintKernel());
  *

  Q.single_task(
	//Capture
	[=]
	//No parameter of the lambda 
	() { //Body
	     sycl::ext::oneapi::experimental::printf("Hello, World!\n"); 
	   }
  );
  // wait the queued submissions to complete
  Q.wait();

  return 0;
}
