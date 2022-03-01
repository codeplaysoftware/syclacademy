# Exercise 2: First SYCL kernels. Using dependencies.

This exercise aims to give an intro to USM functions, single tasks, as well 
as the concept of data dependencies and synchronization.

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

1. Allocate two ints on device, `a=1` and `b=2`. 
2. Memcpy to initialize the device memory for `a_dev`, `b_dev`.
3. Use a `single_task` to multiply `a_dev` by 2.
4. Use a separate `single_task` to multiply `b_dev` by 100.
5. Use a `single_task` to add `a_dev` and `b_dev` together and store the value in `a`.
6. Memcpy the value back to host and print to `std::cout`.

Explicitly link the dependencies for each `single_task` or `memcpy` using 
events, or synchronize with calls to `wait()`. Remember that `wait()` can
be called on an event or a queue.

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
