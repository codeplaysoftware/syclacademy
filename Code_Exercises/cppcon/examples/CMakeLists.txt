#[[
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
]]

add_example(example thread_joinable)
add_example(example thread_join)
add_example(example thread_detach)
add_example(example thread_exception)
add_example(example thread_guard)
add_example(example thread_param_by_val)
add_example(example thread_param_by_ref)
add_example(example thread_lifetime)
add_example(example thread_move)
add_example(example thread_id)
add_example(example mutex_lock_unlock)
add_example(example mutex_lock_guard)
add_example(example mutex_unprotected_data)
add_example(example mutex_unprotected_data_access)
add_example(example mutex_deadlock_single_lock)
add_example(example mutex_deadlock_unique_lock)
add_example(example mutex_lock_ordering_deadlock)
add_example(example async)
add_example(example packaged_task)
add_example(example promise)
add_example(example promise_exception)
add_example(example sequential_transform)
add_example(example sequential_reduce)
add_example(example sequential_transform_reduce)
add_example(example parallel_transform)
add_example(example parallel_reduce)
add_example(example parallel_transform_reduce)

if (${CPPCON_ENABLE_SYCL})
  add_sycl_example(example verify_sycl)
  add_sycl_example(example sycl_error_handling)
  add_sycl_example(example sycl_debugging)
  add_sycl_example(example sycl_logging)
  add_sycl_example(example sycl_barrier)
  add_sycl_example(example sycl_transform)
  add_sycl_example(example sycl_reduce)
  add_sycl_example(example sycl_transform_reduce)
endif()