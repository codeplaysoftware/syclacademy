#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

# TODO(Gordon): Generalize this to support other implementations
function(add_sycl_executable_computecpp prefix source)
  add_executable("${prefix}_${source}" "${source}.cpp")
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
    
  add_test(${source} ${source})
endfunction()

function(add_sycl_executable_dpcpp prefix source)
  #TODO
endfunction()

# Note: This is copy-pasted from the ComputeCpp function,
# we may want to refactor this into a single function.
function(add_sycl_executable_hipsycl prefix source)
  add_executable("${prefix}_${source}" "${source}.cpp")
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
    
  add_test(${source} ${source})
endfunction()

function(add_sycl_executable prefix source)
  if (SYCL_ACADEMY_USE_COMPUTECPP)
    add_sycl_executable_computecpp(${prefix} ${source})
  elseif(SYCL_ACADEMY_USE_DPCPP)
    add_sycl_executable_dpcpp(${prefix} ${source})
  elseif(SYCL_ACADEMY_USE_HIPSYCL)
    add_sycl_executable_hipsycl(${prefix} ${source})
  endif()
endfunction()

add_subdirectory(Exercise_1_Getting_Started)
add_subdirectory(Exercise_2_Configuring_a_Queue)
add_subdirectory(Exercise_3_Hello_World)
add_subdirectory(Exercise_4_Vector_Add)
add_subdirectory(Exercise_5_Image_Grayscale)
add_subdirectory(Exercise_6_Matrix_Transpose)
