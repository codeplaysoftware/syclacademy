#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

add_sycl_executable(More_SYCL_Features reduce_naive)
add_sycl_executable(More_SYCL_Features reduce_atomic)
add_sycl_executable(More_SYCL_Features reduce_group_algorithms)
# SYCL reductions don't have full support in AdaptiveCpp
if (NOT SYCL_ACADEMY_USE_ADAPTIVECPP)
  add_sycl_executable(More_SYCL_Features reduce_sycl_reduction)
endif()
