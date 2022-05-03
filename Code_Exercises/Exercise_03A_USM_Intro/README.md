# Exercise 2: First SYCL kernels. Using depencies.

This exercise aims to give an intro to USM functions: `malloc_device`, `fill` 
and `memcpy`. We'll allocate some memory on the device, fill it, copy it back,
and free the device allocation.

 ---

Compile with 

```
clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda source.cpp
```

To run:
```
SYCL_DEVICE_FILTER=cuda ./a.out
```
---

## Instructions

1. Allocate an int on device.
2. Fill the int
3. Memcpy the int back to host memory.
4. Free the allocated int.

Remember that fill() and mempcy() are asynchronous, so make
sure you `wait()` between fill() and memcpy() or else you
aren't guaranteed to get the expected result.