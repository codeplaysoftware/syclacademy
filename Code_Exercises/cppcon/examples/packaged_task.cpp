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
#include <numeric>
#include <thread>

int add(int x, int y) {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "add function runs in :" << std::this_thread::get_id()
            << std::endl;
  return x + y;
}

void task_thread() {
  std::packaged_task<int(int, int)> task_1(add);
  std::future<int> future_1 = task_1.get_future();
  std::thread thread_1(std::move(task_1), 5, 6);
  thread_1.detach();
  std::cout << "task thread -" << future_1.get() << "\n";
}
void task_normal() {
  std::packaged_task<int(int, int)> task_1(add);
  std::future<int> future_1 = task_1.get_future();
  task_1(7, 8);
  std::cout << "task normal -" << future_1.get() << "\n";
}

int main() {
  task_thread();
  task_normal();
  std::cout << "main thread id :" << std::this_thread::get_id() << std::endl;
  return 0;
}
