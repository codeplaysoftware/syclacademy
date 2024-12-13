#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

add_sycl_executable(OneMKL_gemm source_onemkl_usm_gemm)
add_sycl_executable(OneMKL_gemm source_onemkl_buffer_gemm)

target_link_libraries(OneMKL_gemm_source_onemkl_usm_gemm PUBLIC -L$ENV{MKLROOT} -lonemkl)
target_link_libraries(OneMKL_gemm_source_onemkl_buffer_gemm PUBLIC -L$ENV{MKLROOT} -lonemkl)
if(SYCL_ACADEMY_ENABLE_SOLUTIONS)
  add_sycl_executable(OneMKL_gemm solution_onemkl_usm_gemm)
  add_sycl_executable(OneMKL_gemm solution_onemkl_buffer_gemm)

  target_link_libraries(OneMKL_gemm_solution_onemkl_usm_gemm PUBLIC -L$ENV{MKLROOT} -lonemkl)
  target_link_libraries(OneMKL_gemm_solution_onemkl_buffer_gemm PUBLIC -L$ENV{MKLROOT} -lonemkl)
endif()
