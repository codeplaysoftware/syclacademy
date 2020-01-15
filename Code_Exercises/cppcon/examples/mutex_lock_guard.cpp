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
#include <list>
#include <mutex>
#include <thread>

std::list<int> my_list;
std::mutex m;

void add_to_list(int const& x) {
  std::lock_guard<std::mutex> lg(m);
  my_list.push_back(x);
}
void size() {
  std::lock_guard<std::mutex> lg(m);
  int size = my_list.size();
  std::cout << "size of the list is : " << size << std::endl;
}

int main() {
  size();
  std::thread thread_1(add_to_list, 4);
  size();
  std::thread thread_2(add_to_list, 11);
  size();
  thread_1.join();
  thread_2.join();

  return 0;
}
