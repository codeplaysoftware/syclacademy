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

if (${CPPCON_ENABLE_SYCL})
  add_sycl_example(solution sycl_01_configuring_a_queue)
  add_sycl_example(solution sycl_02_hello_world)
  add_sycl_example(solution sycl_03_vector_add)
  add_sycl_example(solution sycl_04_image_grayscale)
  add_sycl_example(solution sycl_05_matrix_transpose)
endif()
