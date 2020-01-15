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

class list_wrapper {
  std::list<int> my_list;
  std::mutex m;

 public:
  void add_to_list(int const& x) {
    std::lock_guard<std::mutex> lg(m);
    my_list.push_front(x);
  }

  void size() {
    std::lock_guard<std::mutex> lg(m);
    int size = my_list.size();
    std::cout << "size of the list is : " << size << std::endl;
  }
  std::list<int>* get_data() { return &my_list; }
};

int main() { return 0; }
