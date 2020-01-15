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

#ifndef __SYCL_POLICY_H__
#define __SYCL_POLICY_H__

#include <iostream>

#include <CL/sycl.hpp>

namespace cppcon {

template <typename T>
class sycl_execution_policy_t {
 public:
  sycl_execution_policy_t()
      : queue_{cl::sycl::gpu_selector{}, [=](cl::sycl::exception_list eL) {
                 try {
                   for (auto& e : eL) {
                     std::rethrow_exception(e);
                   }
                 } catch (cl::sycl::exception e) {
                   std::cout << "SYCL exception caught: " << e.what() << "\n\n";
                 }
               }} {
    std::cout
        << "SYCL device: "
        << queue_.get_device().template get_info<cl::sycl::info::device::name>()
        << std::endl;

    cl::sycl::program prog(queue_.get_context());
    prog.build_with_kernel_type<T>();
    auto kernel = prog.get_kernel<T>();
    workGroupSize_ = kernel.template get_work_group_info<
        cl::sycl::info::kernel_work_group::work_group_size>(
        queue_.get_device());
  }

  cl::sycl::queue get_queue() const { return queue_; }

  size_t get_work_group_size() const { return workGroupSize_; }

 private:
  cl::sycl::queue queue_;

  size_t workGroupSize_;
};

template <typename T>
using sycl = sycl_execution_policy_t<T>;

}  // namespace cppcon

#endif  // __SYCL_POLICY_H__
