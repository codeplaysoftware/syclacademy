#pragma once

#include <cstddef> // for size_t
#include <iostream>

#define SYCLACADEMY_ASSERT(cond)                                               \
  (static_cast<bool>(cond)                                                     \
       ? void(0)                                                               \
       : __assert_fail(#expr, __FILE__, __LINE__, __ASSERT_FUNCTION))
