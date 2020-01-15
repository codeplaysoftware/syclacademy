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

void hello() { std::cout << "hello from method \n"; }

int main() {
  std::thread thread_1(hello);

  if (thread_1.joinable()) std::cout << "this is joinable thread \n";

  thread_1.join();

  if (thread_1.joinable()) {
    std::cout << "this is joinable thread \n";
  } else {
    std::cout << "After calling join, this is not a joinable thread \n";
  }

  std::cout << "hello from main \n";

  return 0;
}