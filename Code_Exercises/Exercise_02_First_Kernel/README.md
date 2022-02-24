# Exercise 2: First SYCL kernels. Using depencies.

This exercise aims to give an intro to USM functions, single tasks, as well 
as the concept of data dependencies and synchronization.

 ---

Compile with 

```
clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda solution.cpp
```

To run:
```
SYCL_DEVICE_FILTER=somedevice ./a.out
```
---

## Instructions

1. Allocate two ints on device, `a=1` and `b=2`. 
2. Use a `single_task` to multiply `a` by 2.
2. Use a separate `single_task` to multiply `b` by 100.
3. Use a `single_task` to add `a` and `b` together and store the value in `a`.
4. Memcpy the value back to host and print to stdout.

Explicitly name the dependencies for each `single_task` or `memcpy` using 
events, or synchronize with calls to `wait()`.

```
       initialize dev_a, dev_b
        /  \
       V    V
   a *= 2  b *= 100
        \  /
         V
       a += b
         | 
         V
    memcpy back to host and check answer
```

Try to change the result by changing/removing listed dependencies.
