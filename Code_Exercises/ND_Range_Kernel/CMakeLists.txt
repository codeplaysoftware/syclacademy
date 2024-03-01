#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

# Exercise exercise_14_nd_range_kernel
add_sycl_executable(ND_Range_Kernel source)
if(SYCL_ACADEMY_ENABLE_SOLUTIONS)
  add_sycl_executable(ND_Range_Kernel solution)
endif()
