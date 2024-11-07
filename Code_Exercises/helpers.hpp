#pragma once

#include <cstddef> // for size_t
#include <iostream>

#define SYCLACADEMY_ASSERT(cond)                                               \
  if (!(cond)) {                                                               \
    std::cerr << "Failure in " << __FUNCTION__ << std::endl;                   \
    std::abort();                                                              \
  }
