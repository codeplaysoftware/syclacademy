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

#include <functional>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

void print_int(std::future<int>& fut) {
  std::cout << "waiting for value from print thread \n";
  std::cout << "value: " << fut.get() << '\n';
}

int main() {
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();
  std::thread print_thread(print_int, std::ref(fut));
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "setting the value in main thread \n";
  prom.set_value(10);
  print_thread.join();
  return 0;
}
