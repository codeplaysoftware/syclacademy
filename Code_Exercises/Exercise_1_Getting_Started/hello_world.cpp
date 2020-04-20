/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#include <iostream>

#include <CL/sycl.hpp>

class hello_world;

/* This is a basic example to illustrate the main components of a SYCL
 * program. It executes a single-threaded kernel on the default device
 * (as determined by the SYCL implementation) whose only function is to
 * output the canonical "hello world" string. */
int main() {
  /* Selectors determine which device kernels will be dispatched to.
   * Try using a host_selector, too! */
  cl::sycl::default_selector selector;

  /* Queues are used to enqueue work.
   * In this case we construct the queue using the selector. Users can create
   * their own selectors to choose whatever kind of device they might need. */
  cl::sycl::queue myQueue(selector);
  std::cout << "Running on "
            << myQueue.get_device().get_info<cl::sycl::info::device::name>()
            << "\n";

  /* C++ 11 lambda functions can be used to submit work to the queue.
   * They set up data transfers, kernel compilation and the actual
   * kernel execution. This submission has no data, only a "stream" object.
   * Useful in debugging, it is a lot like an std::ostream. The handler
   * object is used to control the scope certain operations can be done. */
  myQueue.submit([&](cl::sycl::handler& cgh) {
    /* The stream object allows output to be generated from the kernel. It
     * takes three parameters in its constructor. The first is the maximum
     * output size in bytes, the second is how large [in bytes] the total
     * output of any single << chain can be, and the third is the cgh,
     * ensuring it can only be constructed inside a submit() call. */
    cl::sycl::stream os(1024, 80, cgh);

    /* single_task is the simplest way of executing a kernel on a
     * SYCL device. A single thread executes the code inside the kernel
     * lambda. The template parameter needs to be a unique name that
     * the runtime can use to identify the kernel (since lambdas have
     * no accessible name). */
    cgh.single_task<hello_world>([=]() {
      /* We use the stream operator on the stream object we created above
       * to print to stdout from the device. */
      os << "Hello, World!\n";
    });
  });

  return 0;
}