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
#include <mutex>

class data_object {
 public:
  void some_operation() { std::cout << "this is some operation \n"; }
};

class data_wrapper {
  data_object protected_data;
  std::mutex m;

 public:
  template <typename function>
  void do_some_work(function f) {
    std::lock_guard<std::mutex> lg(m);
    f(protected_data);
  }
};
data_object* unprotected_data;

void bad_function(data_object& data) { unprotected_data = &data; }

int main() {
  data_wrapper wrapper;
  wrapper.do_some_work(bad_function);

  return 0;
}
