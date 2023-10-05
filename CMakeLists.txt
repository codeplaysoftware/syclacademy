#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.11...3.27)

project (SYCLAcademy)

message(STATUS ">> Top level")

# CMake input options

option(SYCL_ACADEMY_USE_COMPUTECPP "Configure to compile with ComputeCpp" OFF)
option(SYCL_ACADEMY_USE_DPCPP "Configure to compile with Intel DPC++" OFF)
option(SYCL_ACADEMY_USE_HIPSYCL "Configure to compile with AMD hipSYCL" OFF)
option(SYCL_ACADEMY_ENABLE_SOLUTIONS "Include solution files in project" OFF)

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
  message(FATAL_ERROR "No SYCL implementation specified, please specify one of the following "
  "SYCL_ACADEMY_USE_COMPUTECPP, SYCL_ACADEMY_USE_HIPSYCL or SYCL_ACADEMY_USE_DPCPP to ON.")
endif()
if (${SYCL_IMPLEMENTATIONS_USED} GREATER 1)
  message(FATAL_ERROR "Multiple SYCL implementations specified, please specify only one of the following "
  "set one of SYCL_ACADEMY_USE_COMPUTECPP, SYCL_ACADEMY_USE_HIPSYCL or SYCL_ACADEMY_USE_DPCPP to ON.")
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

# No further DPC++ setup required here beyond normal DPC++ installation 

# hipSYCL setup

if (SYCL_ACADEMY_USE_HIPSYCL)
  set(hipSYCL_DIR ${SYCL_ACADEMY_INSTALL_ROOT}/lib/cmake/hipSYCL)
  find_package(hipSYCL CONFIG REQUIRED PATHS)
endif()

# Exercises

enable_testing()
add_subdirectory(External/Catch2)
add_subdirectory(Code_Exercises)

message(STATUS "<< Top level finish")
