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
#include <numeric>
#include <vector>

int MIN_ELEMENT_COUNT = 1000;

template <typename iterator>
int parallal_reduce(iterator begin, iterator end) {
  long length = std::distance(begin, end);
  // atleast runs 1000 element
  if (length <= MIN_ELEMENT_COUNT) {
    std::cout << std::this_thread::get_id() << std::endl;
    return std::accumulate(begin, end, 0);
  }
  iterator mid = begin;
  std::advance(mid, (length + 1) / 2);
  // recursive all to parallel_reduce
  std::future<int> f1 = std::async(std::launch::deferred | std::launch::async,
                                   parallal_reduce<iterator>, mid, end);
  auto sum = parallal_reduce(begin, mid);
  return sum + f1.get();
}

int main() {
  std::vector<int> v(10000, 1);
  std::cout << "The sum is " << parallal_reduce(v.begin(), v.end()) << '\n';
  return 0;
}
