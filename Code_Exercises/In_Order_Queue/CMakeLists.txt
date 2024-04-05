#[[
  SYCL Academy (c)

  SYCL Academy is licensed under a Creative Commons Attribution-ShareAlike 4.0
  International License.

  You should have received a copy of the license along with this work.  If not,
  see <http://creativecommons.org/licenses/by-sa/4.0/>.
]]

# Exercise exercise_11_in_order_queue
add_sycl_executable(In_Order_Queue source_vector_add)
add_sycl_executable(In_Order_Queue source_queue_benchmarking)
if(SYCL_ACADEMY_ENABLE_SOLUTIONS)
  add_sycl_executable(In_Order_Queue solution_vector_add)
  add_sycl_executable(In_Order_Queue solution_queue_benchmarking)
endif()
