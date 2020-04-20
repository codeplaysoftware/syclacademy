/*
Copyright 2019 Gordon Brown

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CL/sycl.hpp>

class hello_world;

TEST_CASE("hello_world", "sycl_02_hello_world") {
  cl::sycl::default_selector selector;

  cl::sycl::queue myQueue(selector);
  std::cout << "Running on "
            << myQueue.get_device().get_info<cl::sycl::info::device::name>()
            << "\n";

  myQueue.submit([&](cl::sycl::handler& cgh) {
    cl::sycl::stream os(1024, 80, cgh);

    cgh.single_task<hello_world>([=]() { os << "Hello World!\n"; });
  });

  myQueue.wait();

  REQUIRE(true);
}

class print_ids;

TEST_CASE("print_ids", "sycl_02_hello_world") {
  cl::sycl::default_selector selector;

  cl::sycl::queue myQueue(selector);
  std::cout << "Running on "
            << myQueue.get_device().get_info<cl::sycl::info::device::name>()
            << "\n";

  myQueue.submit([&](cl::sycl::handler& cgh) {
    cl::sycl::stream os(1024, 80, cgh);

    cgh.parallel_for<print_ids>(cl::sycl::range<1>(1024),
                                [=](cl::sycl::id<1> idx) {
                                  if (idx[0] == 999) {
                                    os << "I am on " << idx << "\n";
                                  }
                                });
  });

  myQueue.wait();

  REQUIRE(true);
}
