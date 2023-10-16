#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

message(STATUS ">> CMake Exercises")
message(STATUS "SYCL_ACADEMY_BUILD_EXERCISES ${SYCL_ACADEMY_BUILD_EXERCISES}")

# CMake function to build a hipSYCL configuration and create executable binaries
# from hipSYCL libraries. 
function( add_sycl_executable_hipSYCL prefix source )
  if(NOT DEFINED ${CMAKE_BUILD_TYPE})
	  set(CMAKE_BUILD_TYPE "DEBUG")
  endif()

  add_executable("${prefix}_${source}" "${source}.cpp")
  target_compile_definitions("${prefix}_${source}" PUBLIC -DSYCL_LANGUAGE_VERSION=2020)
  target_include_directories("${prefix}_${source}" PRIVATE
    ${PROJECT_SOURCE_DIR}/Utilities/include 
    ${PROJECT_SOURCE_DIR}/External/stb)
  target_link_libraries("${prefix}_${source}" PRIVATE Threads::Threads) 
  target_link_libraries("${prefix}_${source}" PUBLIC Catch2::Catch2)
  set_target_properties("${prefix}_${source}" PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)  
endfunction()

# CMake function to build a DPC++ configuration and create executable binaries
# from oneAPI libraries. 
function( add_sycl_executable_dpcpp prefix source )
  if(NOT DEFINED ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "DEBUG")
  endif()

  set(CMAKE_VERBOSE_MAKEFILE ON)
  set(TARGET_NAME "${prefix}_${source}")
      
  add_executable(${TARGET_NAME} "${source}.cpp")
  # This function is from IntelSYCL cmake module
  add_sycl_to_target(TARGET ${TARGET_NAME} SOURCES "${source}.cpp") 
  target_include_directories(${TARGET_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/External/Catch2/single_include")
  target_link_libraries(${TARGET_NAME} PUBLIC Catch2::Catch2)
endfunction()

function( add_sycl_executable exercise_number prefix source )
  # Validate commmand line input arguments
  set(script_argOkCounter 0)
  if(${SYCL_ACADEMY_BUILD_EXERCISES} STREQUAL "ALL")
    math(EXPR script_argOkCounter ${script_argOkCounter}+1)
  endif()
  if(${SYCL_ACADEMY_BUILD_EXERCISES} STREQUAL "${exercise_number}")
    math(EXPR script_argOkCounter ${script_argOkCounter}+1)
  endif()
  if(${script_argOkCounter} EQUAL 0)
    # Skip this exercise, not selected.
    return()
  endif()

  message(STATUS ">> CMake Exercise ${exercise_number} ${source}")
  
  if (SYCL_ACADEMY_USE_DPCPP)
    add_sycl_executable_dpcpp(${prefix} ${source})
  endif()
  if (SYCL_ACADEMY_USE_HIPSYCL)
    add_sycl_executable_hipSYCL(${prefix} ${source})
  endif()

  message(STATUS "<< CMake Exercise ${exercise_number} ${source}")
endfunction()



add_subdirectory(Exercise_01_Compiling_with_SYCL)
add_subdirectory(Exercise_02_Hello_World)
add_subdirectory(Exercise_03_Scalar_Add)
add_subdirectory(Exercise_04_Handling_Errors)
add_subdirectory(Exercise_05_Device_Selection)
add_subdirectory(Exercise_06_Vector_Add)
add_subdirectory(Exercise_07_USM_Selector)
add_subdirectory(Exercise_08_USM_Vector_Add)
add_subdirectory(Exercise_09_Synchronization)
add_subdirectory(Exercise_10_Managing_Dependencies)
add_subdirectory(Exercise_11_In_Order_Queue)
add_subdirectory(Exercise_12_Temporary_Data)
add_subdirectory(Exercise_13_Load_Balancing)
add_subdirectory(Exercise_14_ND_Range_Kernel)
add_subdirectory(Exercise_15_Image_Convolution)
add_subdirectory(Exercise_16_Coalesced_Global_Memory)
add_subdirectory(Exercise_17_Vectors)
add_subdirectory(Exercise_18_Local_Memory_Tiling)
add_subdirectory(Exercise_19_Work_Group_Sizes)

message(STATUS "<< CMake Exercises")
