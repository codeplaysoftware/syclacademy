# SYCL Academy

## Exercise 19: Work Group Sizes
---

In this exercise you will learn how to use different work group sizes in order
to compare the performance difference.

If using ComputeCPP you need to ```#define STBI_NO_SIMD``` before the include ```#include <image_conv.h>```.

---

### 1.) Try different work-group sizes

In order to optimize for occupancy try different work-group sizes, by specifying
a different local range for the `nd_range`.

Note that if the work-group size exceeds the maximum work-group size the target
device supports then it will fail to execute.

Compare the performance of the various work-group sizes you try.

## Build and execution hints
#### ComputeCpp
```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_IMPLEMENTATION_INSTALL_ROOT=/insert/path/to/computecpp ..
make exercise_19_work_group_sizes_source
./Code_Exercises/Exercise_19_Work_Group_Sizes/exercise_19_work_group_sizes_source
```
#### DPC++
```
clang++ -fsycl -I../../External/Catch2/single_include -I../../Utilities/include/ -I../../External/stb solution.cpp
```
