/*
Copyright 2018 Gordon Brown

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

#ifndef __UTILS_H__
#define __UTILS_H__

namespace cppcon {

template <typename ValueType>
class pass {
 public:
  pass() {}

  ValueType operator()(ValueType v) const {
    return v;
  }
};

template <typename ValueType>
class pow {
 public:
  pow(int power) : power_{power} {}

  ValueType operator()(ValueType v) const {
    for (int i = 0; i < power_; i++) {
      v *= v;
    }
    return power_;
  }

 private:
  int power_;
};

}  // namespace cppcon

#endif  // __UTILS_H__
