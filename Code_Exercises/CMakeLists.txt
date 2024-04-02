#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

# CMake function to build ab AdaptiveCpp configuration and create executable binaries
function( add_sycl_executable_adaptivecpp prefix source )
  set(TARGET_NAME "${prefix}_${source}")
  add_executable("${TARGET_NAME}" "${source}.cpp")
  add_sycl_to_target(TARGET ${TARGET_NAME} SOURCES "${source}.cpp") 
  
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
  set(TARGET_NAME "${prefix}_${source}")
      
  add_executable(${TARGET_NAME} "${source}.cpp")
  # This function is from IntelSYCL cmake module
  add_sycl_to_target(TARGET ${TARGET_NAME} SOURCES "${source}.cpp") 
  target_include_directories(${TARGET_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/External/Catch2/single_include")
  target_include_directories(${TARGET_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/External/stb")
  target_include_directories(${TARGET_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Utilities/include")
  target_link_libraries(${TARGET_NAME} PUBLIC Catch2::Catch2)
endfunction()

function( add_sycl_executable prefix source )
  if (SYCL_ACADEMY_USE_DPCPP)
    add_sycl_executable_dpcpp(${prefix} ${source})
  endif()
  if (SYCL_ACADEMY_USE_ADAPTIVECPP)
    add_sycl_executable_adaptivecpp(${prefix} ${source})
  endif()
endfunction()



add_subdirectory(Compiling_with_SYCL)
add_subdirectory(Hello_World)
add_subdirectory(Scalar_Add)
add_subdirectory(Handling_Errors)
add_subdirectory(Device_Selection)
add_subdirectory(Vector_Add)
add_subdirectory(USM_Selector)
add_subdirectory(USM_Vector_Add)
add_subdirectory(Synchronization)
add_subdirectory(Managing_Dependencies)
add_subdirectory(In_Order_Queue)
add_subdirectory(Temporary_Data)
add_subdirectory(Load_Balancing)
add_subdirectory(ND_Range_Kernel)
add_subdirectory(Image_Convolution)
add_subdirectory(Coalesced_Global_Memory)
add_subdirectory(Vectors)
add_subdirectory(Functors)
add_subdirectory(Local_Memory_Tiling)
add_subdirectory(Work_Group_Sizes)
