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

#include <iostream>
#include <thread>

void func_1() { std::cout << "This is a function 1\n"; }
void func_2() { std::cout << "This is a function 2\n"; }

int main() {
  std::thread thread_1(func_1);
  /* Fails as std::thread has no copy constructor s*/
  // std::thread thread_2 = thread_1;
  std::thread thread_2 = std::move(thread_1);
  thread_1 = std::thread(func_2);
  std::thread thread_3 = std::move(thread_2);
  /* Later thread_3.join() will fail as this std::move would invalidate it */
  // thread_1 = std::move(thread_3);
  thread_1.join();
  thread_3.join();
  return 0;
}
