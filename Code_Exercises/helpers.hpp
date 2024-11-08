#pragma once

#include <cstddef> // for size_t
#include <iostream>

#define SYCLACADEMY_ASSERT(cond)                                               \
  if (!(cond)) {                                                               \
    std::cerr << "Failure in " << __BASE_FILE__ << ":" << __FUNCTION__         \
              << std::endl;                                                    \
    std::abort();                                                              \
  }
