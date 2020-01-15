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

#ifndef __STD_POLICIES_H__
#define __STD_POLICIES_H__

namespace cppcon {

struct seq_execution_policy_t {};
struct par_execution_policy_t {};
struct par_unseq_execution_policy_t {};

constexpr seq_execution_policy_t seq{};
constexpr par_execution_policy_t par{};
constexpr par_unseq_execution_policy_t par_unseq{};

}  // namespace cppcon

#endif  // __STD_POLICIES_H__
