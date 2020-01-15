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

class reverse;

void parallel_reverse(std::vector<float> &i, std::vector<float> &o) {
  using namespace cl::sycl;

  queue defaultQueue;

  buffer<float, 1> iBuf(i.data(), range<1>(i.size()));
  buffer<float, 1> oBuf(o.data(), range<1>(o.size()));

  defaultQueue.submit([&](handler &cgh) {
    auto iAcc = iBuf.get_access<access::mode::read>(cgh);
    auto oAcc = oBuf.get_access<access::mode::write>(cgh);

    accessor<float, 1, access::mode::read_write, access::target::local> scratch(
        128, cgh);

    cgh.parallel_for<reverse>(
        nd_range<1>(range<1>(i.size()), range<1>(128)), [=](nd_item<1> item) {
          scratch[item.get_local_id(0)] = iAcc[item.get_global_id(0)];
          item.barrier(access::fence_space::local_space);
          oAcc[item.get_global_id(0)] = 128 - scratch[item.get_local_id(0)];
        });
  });
}

TEST_CASE("barrier", "sycl_barrier") {
  const int size = 1024;

  std::vector<float> a(size), o(size);

  for (int i = 0; i < size; i++) {
    a[i] = static_cast<float>(i % 128);
    o[i] = 0.0f;
  }

  parallel_reverse(a, o);

  for (int g = 0; g < (size / 128); g++) {
    for (int i = 0; i < 128; i++) {
      REQUIRE(o[(g * 128) + i] == static_cast<float>(128 - i));
    }
  }
  REQUIRE(true);
}
