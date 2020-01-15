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
#include <thread>

void func_2(int& x) {
  while (true) {
    std::cout << x << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void func_1() {
  int x = 5;
  std::thread thread_2(func_2, std::ref(x));
  /* Aborts if detach is not called here */
  thread_2.detach();
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "thread_1 finished execution \n";
}
int main() {
  std::thread thread_1(func_1);
  thread_1.join();
  /* Access violation if you sleep here */
  // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  return 0;
}
