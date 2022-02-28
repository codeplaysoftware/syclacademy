# Exercise 6: Vector Add

---

In this exercise you will learn how add the values in two arrays and write the
results to another array in parallel using `parallel_for`.

---

To compile:
```
clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda solution.cpp
```

To run:
```
SYCL_DEVICE_FILTER=cuda ./a.out
```
---
