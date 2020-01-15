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

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

class thread_guard {
  std::thread& t;

 public:
  explicit thread_guard(std::thread& _t) : t(_t) {}
  ~thread_guard() {
    if (t.joinable()) {
      t.join();
    }
  }
  thread_guard(const thread_guard&) = delete;
  thread_guard& operator=(const thread_guard&) = delete;
};

void hello() { std::cout << "hello from method \n"; }
void other_operations() {
  std::cout << "hello from other operation \n";
  throw std::runtime_error("this is a runtime error");
}

int main() {
  std::thread thread_1(hello);
  thread_guard tg(thread_1);
  try {
    other_operations();  // do other operations
  } catch (...) {
  }
  return 0;
}
