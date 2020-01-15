/*
Copyright 2018 Michael Wong

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

#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <cmath>

void throw_exception() {
  throw std::invalid_argument("input cannot be negative");
}

void calculate_squre_root(std::promise<int>& prom) {
  int x = 1;
  std::cout << "Please, enter an integer value: ";
  try {
    std::cin >> x;
    if (x < 0) {
      throw_exception();
    }
    prom.set_value(std::sqrt(x));
  } catch (std::exception&) {
    prom.set_exception(std::current_exception());
  }
}

void print_result(std::future<int>& fut) {
  try {
    int x = fut.get();
    std::cout << "value: " << x << '\n';
  } catch (std::exception& e) {
    std::cout << "[exception caught: " << e.what() << "]\n";
  }
}

int main() {
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();

  std::thread printing_thread(print_result, std::ref(fut));
  std::thread calculation_thread(calculate_squre_root, std::ref(prom));

  printing_thread.join();
  calculation_thread.join();
  return 0;
}
