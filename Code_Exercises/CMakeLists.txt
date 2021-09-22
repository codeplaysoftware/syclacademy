#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

function(add_sycl_executable prefix source)
  add_executable("${prefix}_${source}" "${source}.cpp")
  target_compile_definitions("${prefix}_${source}" PUBLIC
    -DSYCL_LANGUAGE_VERSION=2020)
  if(${SYCL_ACADEMY_USE_COMPUTECPP})
    target_compile_definitions("${prefix}_${source}" PUBLIC -DSYCL_ACADEMY_USE_COMPUTECPP)
  endif()
  target_include_directories("${prefix}_${source}" PRIVATE
    ${PROJECT_SOURCE_DIR}/Utilities/include ${PROJECT_SOURCE_DIR}/External/stb)
  target_link_libraries("${prefix}_${source}" PRIVATE Threads::Threads)
  target_link_libraries("${prefix}_${source}" PUBLIC Catch2::Catch2)
  set_target_properties("${prefix}_${source}" PROPERTIES CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

  add_sycl_to_target(
    TARGET "${prefix}_${source}"
    SOURCES "${source}.cpp"
  )
    
  add_test(${prefix}_${source} ${prefix}_${source})
endfunction()

function(add_sycl_executable_dpcpp prefix source)
  # Not implemented
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
