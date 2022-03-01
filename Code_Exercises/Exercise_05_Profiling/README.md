# Exercise 5: Optimization and Profiling

This exercise gives a fully functioning example of a SYCL reduction. 

Some elements of the implementation are sub-optimal. Use optimization 
heuristics to make code run faster.

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

## Optimization Principles

* Coalesce global memory accesses. Adjacent work items should access adjacent 
elements in memory.
* Inline functions when possible.
* Check different workgroup sizes and choose an optimal workgroup size.
