#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.

  Invoking CMake from the command line example usage:
  cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
]]

# Minimum version required by
# /opt/intel/oneapi/compiler/latest/linux/IntelSYCL/ReadMeSYCL.txt
if(WIN32)
  cmake_minimum_required(VERSION 3.23...3.27)
else()
  cmake_minimum_required(VERSION 3.20...3.27)
endif()

project (SYCLAcademy)

# CMake input options

option(SYCL_ACADEMY_USE_DPCPP "Configure to compile with Intel DPC++" OFF)
option(SYCL_ACADEMY_USE_ADAPTIVECPP "Configure to compile with AdaptiveCpp" OFF)
option(SYCL_ACADEMY_ENABLE_SOLUTIONS "Include solution source files in the project" OFF)

# Variables

set(SYCL_ACADEMY_INSTALL_ROOT CACHE STRING "NOT-FOUND")
set(SYCL_IMPLEMENTATIONS_USED 0)
if(SYCL_ACADEMY_USE_DPCPP)
  math(EXPR SYCL_IMPLEMENTATIONS_USED ${SYCL_IMPLEMENTATIONS_USED}+1)
endif()
if(SYCL_ACADEMY_USE_ADAPTIVECPP)
  math(EXPR SYCL_IMPLEMENTATIONS_USED ${SYCL_IMPLEMENTATIONS_USED}+1)
endif()

if (${SYCL_IMPLEMENTATIONS_USED} EQUAL 0)
  message(FATAL_ERROR "No SYCL implementation specified, please set one of the following "
  "SYCL_ACADEMY_USE_ADAPTIVECPP or SYCL_ACADEMY_USE_DPCPP to ON.")
endif()
if (${SYCL_IMPLEMENTATIONS_USED} GREATER 1)
  message(FATAL_ERROR "Multiple SYCL implementations specified, please set only one of the following "
  "set one of SYCL_ACADEMY_USE_ADAPTIVECPP or SYCL_ACADEMY_USE_DPCPP to ON. ")
endif()

# Common setup

find_package(Threads REQUIRED)
add_subdirectory(Utilities)

# DPC++ setup

if (SYCL_ACADEMY_USE_DPCPP)
  if (${CMAKE_CXX_COMPILER} MATCHES icpx)
    # For DPCPP module to work, find_package to work, use the options
    # -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx on the command line.
    find_package(IntelSYCL REQUIRED)
    if (DEFINED SYCL_TRIPLE)
      list(APPEND CMAKE_CXX_FLAGS "-fsycl-targets=${SYCL_TRIPLE}")
      string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
    if (DEFINED AMD_ARCH)
      if (NOT DEFINED ROCM_DIR)
        message(FATAL_ERROR "Must specify ROCM_DIR when using icpx with rocm")
      endif()
      list(APPEND CMAKE_CXX_FLAGS "-fsycl-targets=amdgcn-amd-amdhsa" "-Xsycl-target-backend" "--offload-arch=${AMD_ARCH}" "--rocm-path=${ROCM_DIR}")
      string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
  else()
    # Open source clang++ doesn't have IntelSYCL cmake module
    function(add_sycl_to_target)
      set(options)
      set(one_value_args TARGET)
      set(multi_value_args SOURCES)
      cmake_parse_arguments(SYCL
        ""
        "${one_value_args}"
        "${multi_value_args}"
        ${ARGN})
      target_compile_options(${SYCL_TARGET} PRIVATE "-fsycl"
        "$<$<BOOL:${SYCL_TRIPLE}>:-fsycl-targets=${SYCL_TRIPLE}>" # Add -fsycl-targets if SYCL_TRIPLE is set
        "$<$<BOOL:${AMD_ARCH}>:-fsycl-targets=amdgcn-amd-amdhsa;-Xsycl-target-backend;--offload-arch=${AMD_ARCH}>") # Add AMD_ARCH if set
      target_link_options(${SYCL_TARGET} PRIVATE "-fsycl"
        "$<$<BOOL:${SYCL_TRIPLE}>:-fsycl-targets=${SYCL_TRIPLE}>" # Add -fsycl-targets if SYCL_TRIPLE is set
        "$<$<BOOL:${AMD_ARCH}>:-fsycl-targets=amdgcn-amd-amdhsa;-Xsycl-target-backend;--offload-arch=${AMD_ARCH}>") # Add AMD_ARCH if set
      target_link_libraries(${SYCL_TARGET} PUBLIC libsycl.so)
    endfunction()
  endif()
endif()

# AdaptiveCpp setup

if (SYCL_ACADEMY_USE_ADAPTIVECPP)
  if (NOT SYCL_ACADEMY_INSTALL_ROOT)
  message(FATAL_ERROR "SYCL implementation root not provided, please specify "
    "the path to the root of the chosen SYCL implementation using "
    "SYCL_ACADEMY_INSTALL_ROOT=<path/to/install/root>.")
  endif()
  set(AdaptiveCpp_DIR ${SYCL_ACADEMY_INSTALL_ROOT}/lib/cmake/AdaptiveCpp)
  find_package(AdaptiveCpp CONFIG REQUIRED PATHS)
endif()

# Exercises

enable_testing()
add_subdirectory(External/Catch2)
add_subdirectory(Code_Exercises)

# Create the Image directory
# Set source and destination paths
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Code_Exercises/Images/")
set(DESTINATION_DIR "${CMAKE_BINARY_DIR}/Code_Exercises/Images/")

# Copy all files from source to destination using file(COPY ...)
file(COPY ${SOURCE_DIR} DESTINATION ${DESTINATION_DIR})
