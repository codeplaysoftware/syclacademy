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

#include <benchmark.h>
#include <utils.h>
#include <std_execution>

constexpr int size = 2097152;
constexpr int iterations = 10;

TEST_CASE("cppcon::transform_reduce(par)", "parallel_transform_reduce") {
  int result{0};
  int expected{0};

  {
    auto input = std::vector<int>(size);

    cppcon::init_data(input,
                      [](int &value, unsigned index) { value = index % 16; });

    cppcon::benchmark(
        [&]() {
          result = cppcon::transform_reduce(cppcon::par, input.begin(),
                                            input.end(), 42, std::plus<>(),
                                            cppcon::pow<int>{100});
        },
        iterations, "cppcon::transform_reduce(par)");
  }

  {
    auto input = std::vector<int>(size);
    auto temp = std::vector<int>(size);

    cppcon::init_data(input,
                      [](int &value, unsigned index) { value = index % 16; });

    cppcon::benchmark(
        [&]() {
          std::transform(input.begin(), input.end(), temp.begin(),
                         cppcon::pow<int>{100});

          expected = std::accumulate(temp.begin(), temp.end(), 42);
        },
        iterations, "std::transform & std::accumulate");
  }

  REQUIRE(result == expected);
}
