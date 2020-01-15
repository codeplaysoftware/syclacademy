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

function(add_example prefix example)
	add_executable("${prefix}_${example}" "${example}.cpp")
    target_include_directories("${prefix}_${example}" PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/external/catch2)
	target_link_libraries("${prefix}_${example}" PRIVATE Threads::Threads)
    set_target_properties("${prefix}_${example}" PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
    add_test(${prefix}_${example} ${prefix}_${example})
endfunction()

function(add_sycl_example prefix example)
	add_executable("${prefix}_${example}" "${example}.cpp")
    target_include_directories("${prefix}_${example}" PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/external/catch2)
	target_link_libraries("${prefix}_${example}" PRIVATE Threads::Threads)
    set_target_properties("${prefix}_${example}" PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

    add_sycl_to_target(
      TARGET "${prefix}_${example}"
      SOURCES "${example}.cpp"
    )

    add_test(${prefix}_${example} ${prefix}_${example})
endfunction()