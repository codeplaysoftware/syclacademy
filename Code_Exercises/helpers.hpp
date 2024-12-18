/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#pragma once

#include <cstddef>  // for size_t
#include <type_traits>
#include <utility>

#ifndef __SYCL_DEVICE_ONLY__
#include <cstdio>   // fprintf
#include <cstdlib>  // abort
#define SYCLACADEMY_ASSERT(cond)                                         \
  do {                                                                   \
    if (!(cond)) {                                                       \
      std::fprintf(stderr, "[FAILURE] %s failed in %s:%d:%s\nExiting\n", \
                   #cond, __BASE_FILE__, __LINE__, __FUNCTION__);        \
      std::abort();                                                      \
    } else {                                                             \
      std::printf("[SUCCESS] Test passed\n");                            \
    }                                                                    \
  } while (false)
#else
#define SYCLACADEMY_ASSERT(cond) void(0)
#endif

#define SYCLACADEMY_ASSERT_EQUAL(lhs, rhs) \
  SYCLACADEMY_ASSERT(SYCLAcademy::equal(lhs, rhs))

namespace SYCLAcademy {

template <typename, typename = void, typename = void>
struct is_vector : std::false_type {};

template <typename T>
struct is_vector<T, std::void_t<decltype(std::declval<T>()[size_t{}])>,
                 std::void_t<decltype(std::declval<T>().size())> >
    : std::true_type {};

template <typename T>
constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>
constexpr size_t get_size(T&& container) {
  using TT = std::remove_reference_t<T>;
  if constexpr (std::is_array_v<TT>) {
    return std::extent_v<TT>;
  } else if constexpr (is_vector_v<TT>) {
    return container.size();
  }
  return 0;
}

/**
 * @brief Generic equality comparison
 *
 * Pointer types are not allowed.
 *
 * @param lhs can be a fundamental type, an object, an array or a vector-like
 * type (has operator[] and method size())
 * @param rhs allowed types depend on lhs type; it can be always a fundamental
 * type or an object; if lhs is an array or vector-like type then it can be an
 * array or vector-like type (for element-wise comparison) or a lambda taking
 * size_t index as parameter (for element-wise comparison to the return value
 * of lambda(index))
 */
template <typename T, typename U>
constexpr bool equal(T&& lhs, U&& rhs) {
  using TT = std::remove_reference_t<T>;
  using UU = std::remove_reference_t<U>;
  static_assert(!std::is_pointer_v<TT> && !std::is_pointer_v<UU>);
  if constexpr (std::is_array_v<TT> || is_vector_v<TT>) {
    const size_t lhs_size{get_size(std::forward<T>(lhs))};
    if constexpr (std::is_array_v<UU> || is_vector_v<UU>) {
      //
      // Compare array/vector to array/vector element-wise
      //
      const size_t rhs_size{get_size(std::forward<U>(rhs))};
      if (lhs_size < 1 || lhs_size != rhs_size) {
        return false;
      }
      for (size_t i{0}; i < lhs_size; ++i) {
        if (lhs[i] != rhs[i]) return false;
      }
      return true;
    } else if constexpr (std::is_invocable_v<UU, size_t>) {
      //
      // Compare array/vector to lambda(index) element-wise
      //
      for (size_t i{0}; i < lhs_size; ++i) {
        if (lhs[i] != rhs(i)) return false;
      }
      return true;
    } else {
      //
      // Compare all elements of an array/vector to a single value
      //
      for (size_t i{0}; i < lhs_size; ++i) {
        if (lhs[i] != rhs) return false;
      }
      return true;
    }
  } else {
    //
    // Single value comparison
    //
    static_assert(!std::is_array_v<UU> && !is_vector_v<UU>);
    return lhs == rhs;
  }
}
}  // namespace SYCLAcademy
