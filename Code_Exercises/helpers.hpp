/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#pragma once

#include <cstddef>  // for size_t

#ifndef __SYCL_DEVICE_ONLY__
#include <cstdio>   // fprintf
#include <cstdlib>  // abort
#define SYCLACADEMY_ASSERT(cond)                                    \
  if (!(cond)) {                                                    \
    std::fprintf(stderr, "%s failed in %s:%d:%s\nExiting\n", #cond, \
                 __BASE_FILE__, __LINE__, __FUNCTION__);            \
    std::abort();                                                   \
  }
#else
#define SYCLACADEMY_ASSERT(cond) void(0);
#endif
