/*
Copyright 2018 Gordon Brown

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
#include <catch.hpp>

#include <CL/sycl.hpp>

class add;

void parallel_add(std::vector<float> &a, std::vector<float> &b,
                  std::vector<float> &o) {
  using namespace cl::sycl;

  try {
    queue defaultQueue([=](exception_list eL) {
      for (auto e : eL) {
        std::rethrow_exception(e);
      }
    });

    buffer<float, 1> aBuf(a.data(), range<1>(a.size()));
    buffer<float, 1> bBuf(b.data(), range<1>(a.size()));
    buffer<float, 1> oBuf(o.data(), range<1>(a.size()));

    defaultQueue.submit([&](handler &cgh) {
      auto aAcc = aBuf.get_access<access::mode::read>(cgh);
      auto bAcc = bBuf.get_access<access::mode::read>(cgh);
      auto oAcc = oBuf.get_access<access::mode::write>(cgh);

      cgh.parallel_for<add>(range<1>(a.size()),
                            [=](id<1> i) { oAcc[i] = aAcc[i] + bAcc[i]; });
    });

    defaultQueue.wait_and_throw();
  } catch (exception e) {
    std::cout << "exception caught : " << e.what() << "\n";
  }
}

TEST_CASE("vector_add", "sycl_vector_add") {
  const int size = 1024;

  std::vector<float> a(size), b(size), o(size);

  for (int i = 0; i < size; i++) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i);
    o[i] = 0.0f;
  }

  parallel_add(a, b, o);

  for (int i = 0; i < size; i++) {
    REQUIRE(o[i] == static_cast<float>(i * 2));
  }
}