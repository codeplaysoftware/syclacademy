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

cmake_minimum_required (VERSION 3.7.2)
project (cppcon2018-parallelism-class)

# Options

option(CPPCON_ENABLE_SYCL "Enable SYCL. Requires ComputeCpp for SYCL examples" ON)
option(CPPCON_ENABLE_SOLUTIONS "Enable soltuions." OFF)

# Dependencies

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(Threads REQUIRED)
if (${CPPCON_ENABLE_SYCL})
  find_package(ComputeCpp REQUIRED)
endif()

# Headers

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/external/catch2)
include_directories(${CMAKE_SOURCE_DIR}/external/stb)

file(GLOB PARALLELISM_INCLUDES ${CMAKE_SOURCE_DIR}/include/*.h)
source_group("Parallelism Headers" FILES ${PARALLELISM_INCLUDES})

# Examples, sources and solutions

enable_testing()

include(${CMAKE_MODULE_PATH}/TestingFunctions.cmake)

add_subdirectory(examples)
add_subdirectory(source)
if (${CPPCON_ENABLE_SOLUTIONS})
  add_subdirectory(solutions)
endif()
