#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.

  Envoking CMake from the command line example usage:
  cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_BUILD_EXERCISES=2 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
]]

# Minimum version required by
# /opt/intel/oneapi/compiler/latest/linux/IntelSYCL/ReadNeSYCL.txt
if(WIN32)
  cmake_minimum_required(VERSION 3.23...3.27)
else()
  cmake_minimum_required(VERSION 3.20...3.27)
endif()

project (SYCLAcademy)

message(STATUS ">> Top level")

# CMake input options

option(SYCL_ACADEMY_USE_COMPUTECPP "Configure to compile with ComputeCpp" OFF)
option(SYCL_ACADEMY_USE_DPCPP "Configure to compile with Intel DPC++" OFF)
option(SYCL_ACADEMY_USE_HIPSYCL "Configure to compile with AMD hipSYCL" OFF)
option(SYCL_ACADEMY_ENABLE_SOLUTIONS "Include solution source files in the project" OFF)
set(SYCL_ACADEMY_BUILD_EXERCISES "ALL" CACHE STRING 
  "State which exercises to build. ALL = build all or give a number for a particular exercise.")

# Variables

set(SYCL_ACADEMY_INSTALL_ROOT CACHE STRING "NOT-FOUND")
set(SYCL_IMPLEMENTATIONS_USED 0)
if(SYCL_ACADEMY_USE_COMPUTECPP)
  math(EXPR SYCL_IMPLEMENTATIONS_USED ${SYCL_IMPLEMENTATIONS_USED}+1)
endif()
if(SYCL_ACADEMY_USE_DPCPP)
  math(EXPR SYCL_IMPLEMENTATIONS_USED ${SYCL_IMPLEMENTATIONS_USED}+1)
endif()
if(SYCL_ACADEMY_USE_HIPSYCL)
  math(EXPR SYCL_IMPLEMENTATIONS_USED ${SYCL_IMPLEMENTATIONS_USED}+1)
endif()

if (${SYCL_IMPLEMENTATIONS_USED} EQUAL 0)
  message(FATAL_ERROR "No SYCL implementation specified, please set one of the following "
  "SYCL_ACADEMY_USE_COMPUTECPP, SYCL_ACADEMY_USE_HIPSYCL or SYCL_ACADEMY_USE_DPCPP to ON.")
endif()
if (${SYCL_IMPLEMENTATIONS_USED} GREATER 1)
  message(FATAL_ERROR "Multiple SYCL implementations specified, please set only one of the following "
  "set one of SYCL_ACADEMY_USE_COMPUTECPP, SYCL_ACADEMY_USE_HIPSYCL or SYCL_ACADEMY_USE_DPCPP to ON. "
  "Clear the CMake cache (delete the build directory) if a previous option was entered.")
endif()
set(script_argOkCounter 0)
set(script_maxExerciseNumber 19)
if (${SYCL_ACADEMY_BUILD_EXERCISES} GREATER ${script_maxExerciseNumber})
  message(FATAL_ERROR "Exercise ${SYCL_ACADEMY_BUILD_EXERCISES} does not exist. "
  "Please specify an exercise number between 1 and ${script_maxExerciseNumber}.")
endif()
if (${SYCL_ACADEMY_BUILD_EXERCISES} GREATER 0)
  math(EXPR script_argOkCounter ${script_argOkCounter}+1)
endif()
if (${SYCL_ACADEMY_BUILD_EXERCISES} STREQUAL "ALL")
  math(EXPR script_argOkCounter ${script_argOkCounter}+1)
endif()
if (${script_argOkCounter} EQUAL 0)
  message(FATAL_ERROR "Option SYCL_ACADEMY_BUILD_EXERCISES was not specified. The option can be specified with either "
  "ALL or the number of the exercise i.e. 3 equals build exercise 3.")
endif()

# Common setup

if(SYCL_ACADEMY_USE_COMPUTECPP)
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/External/computecpp-sdk/cmake/Modules/")
endif()
find_package(Threads REQUIRED)
add_subdirectory(Utilities)

# ComputeCpp setup

if (SYCL_ACADEMY_USE_COMPUTECPP)
 if (NOT SYCL_ACADEMY_INSTALL_ROOT)
  message(FATAL_ERROR "SYCL implementation root not provided, please specify "
    "the path to the root of the chosen SYCL implementation using "
    "SYCL_ACADEMY_INSTALL_ROOT=<path/to/install/root>.")
  endif()
  set(ComputeCpp_DIR ${SYCL_ACADEMY_INSTALL_ROOT})
  include(External/computecpp-sdk/cmake/Modules/ComputeCppCompilerChecks.cmake)
  find_package(ComputeCpp REQUIRED)
endif()

# DPC++ setup 

if (SYCL_ACADEMY_USE_DPCPP)
# For DPCPP module to work, find_package to work, use the options
# -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx on the command line.
# See /opt/intel/oneapi/compiler/latest/linux/IntelSYCL/ReadMeSYCL.txt
  set(dpcpp_DIR /opt/intel/oneapi/compiler/latest/linux/IntelSYCL)
  find_package(IntelSYCL REQUIRED)
endif()

# hipSYCL setup

if (SYCL_ACADEMY_USE_HIPSYCL)
  if (NOT SYCL_ACADEMY_INSTALL_ROOT)
  message(FATAL_ERROR "SYCL implementation root not provided, please specify "
    "the path to the root of the chosen SYCL implementation using "
    "SYCL_ACADEMY_INSTALL_ROOT=<path/to/install/root>.")
  endif()
  set(hipSYCL_DIR ${SYCL_ACADEMY_INSTALL_ROOT}/lib/cmake/hipSYCL)
  find_package(hipSYCL CONFIG REQUIRED PATHS)
endif()

# Exercises

enable_testing()
add_subdirectory(External/Catch2)
add_subdirectory(Code_Exercises)

message(STATUS "<< Top level finish")
