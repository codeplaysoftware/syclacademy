/***************************************************************************
 *  Copyright (C) 2016 Codeplay Software Limited
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  hello-world.cpp
 **************************************************************************/

#include <SYCL/sycl.hpp>

#include <iostream>

/* Basic example to illustrate the main components of a SYCL program. */
int main(int argc, char* argv[]) {
  /* Selectors determine what device kernels will be dispatched to.
   * Try using a host_selector, too! */
  cl::sycl::cpu_selector selector;

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
    /* In a stream, the first number is the total output size, the second
     * is how long any single statement can be, and the third arg is the
     * cgh, ensuring it can only be constructed inside a submit() call. */
    cl::sycl::stream os(1024, 256, cgh);

    /* single_task is the simplest way of executing a kernel on a
     * SYCL device. A single thread executes the code inside the kernel
     * lambda. The template parameter needs to be a unique name that
     * the runtime can use to identify the kernel (since lambdas have
     * no accessible name). */
    cgh.single_task<class hello>([=]() { os << "Hello World!\n"; });
  });

  return 0;
}
