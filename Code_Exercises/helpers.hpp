/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#pragma once

#include <cstddef> // for size_t

#ifndef __SYCL_DEVICE_ONLY__
extern "C" void __assert_fail(const char* __assertion, const char* __file,
                              unsigned int __line, const char* __function);

#define SYCLACADEMY_ASSERT(cond)                                               \
  (static_cast<bool>(cond)                                                     \
       ? void(0)                                                               \
       : __assert_fail(#cond, __FILE__, __LINE__, __FUNCTION__))
#else
#define SYCLACADEMY_ASSERT(cond) void(0);
#endif
