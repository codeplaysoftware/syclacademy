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

#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace cppcon {

template <typename Unit>
struct unit_extension;

template <>
struct unit_extension<std::milli> {
  inline static const char *value = "ms";
};

template <>
struct unit_extension<std::micro> {
  inline static const char *value = "us";
};

template <>
struct unit_extension<std::nano> {
  inline static const char *value = "ns";
};

template <typename Unit>
const char *unit_extension_v = unit_extension<Unit>::value;

template <typename Unit>
void print_time(std::string tag,
                std::chrono::duration<double, std::milli> timeTaken) {
  std::cout << tag << ": "
            << std::chrono::duration_cast<std::chrono::duration<double, Unit>>(
                   timeTaken)
                   .count()
            << unit_extension_v<Unit> << "\n";
}

template <>
void print_time<std::milli>(
    std::string tag, std::chrono::duration<double, std::milli> timeTaken) {
  std::cout << tag << ": " << timeTaken.count()
            << unit_extension_v<std::milli> << "\n";
}

template <typename InitFunc, typename ValueType>
void init_data(std::vector<ValueType> &vec, InitFunc initFunc) {
  for (int i = 0; i < vec.size(); i++) {
    initFunc(vec[i], i);
  }
}

template <typename Func>
auto benchmark(Func &&func, int iterations, std::string caption) {
  std::cout << caption << " (" << iterations << " iterations) \n";
  unsigned completion = 0;
  std::cout << "[";
  std::chrono::duration<double, std::milli> totalTime{0};
  for (int i = 0; i < iterations; i++) {
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    func();
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    totalTime += (end - start);
    unsigned progress =
        static_cast<unsigned>((((i + 1) * 78) / iterations)) - completion;
    for (unsigned c = 0; c < progress; c++) {
      std::cout << "-";
    }
    completion += progress;
  }
  std::cout << "]\n";
  auto averageTime = totalTime / iterations;

  std::cout << ": " << averageTime.count()
            << unit_extension_v<std::milli> << "\n\n";

  return averageTime;
}

void print(const std::vector<int> &vec, std::string tag) {
  std::cout << tag << ": ";
  for (auto e : vec) {
    std::cout << e << ", ";
  }
  std::cout << "\n";
}

}  // namespace cppcon

#endif  // __BENCHMARK_H__
