# SYCL Academy

## Exercise 16: Coalesced Global Memory
---

In this exercise you will learn how to apply row-major and column-major when
linearizing the global id in order to compare the performance difference due to
coalesced global memory access.

---

### 1.) Evaluate global memory access

Now that you have a working grayscaling kernel you should evaluate whether the
global memory access patterns in your kernel are coalesced.

Consider two alternative ways to linearize the global id:

```
auto rowMajorLinearId    = (idx[1] * width) + idx[0];  // row-major
auto columnMajorLinearId = (idx[0] * height) + idx[1];  // column-major
```

Try using both of these and compare the execution time of each.

## Build and execution hints

```
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make coalesced_global_memory_source
./Code_Exercises/Exercise_16_Coalesced_Global_Memory/coalesced_global_memory_source
```
