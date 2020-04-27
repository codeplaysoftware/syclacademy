project(tutorial)
cmake_minimum_required(VERSION 3.2.2)


include(FindComputeCpp.cmake)

# Set include ComputeCpp directories
#include_directories(SYSTEM ${COMPUTECPP_INCLUDE_DIRECTORY})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(hello-world)
add_subdirectory(vector-ops)
add_subdirectory(image-ops)


