# Exercise 4: ND Ranges and Local Memory

This exercise aims to give an intro to ND ranges and a first example
of shared memory usage.

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

Using local memory, flip an array so that `in[0] = out[sz-1]`
and `in[j] = out[j-1].