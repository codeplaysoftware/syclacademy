## Exercise: Local Memory Matrix Transpose
---

In this exercise you will learn how to cache global memory into local memory in
tiles according to work-groups in order to compare the performance difference. 

In order to get good performance, make sure that global memory accesses are 
coalesced. Local memory accesses do not have as large a penalty for
uncoalesced memeory accesses.

---

Compile with 

```
clang++ -fsycl -fsycl-targets=<triple> source.cpp \
  -I../../External/Catch2/single_include -I../../Utilities/include
```

### 1.) Use local memory

Allocate local memory for the kernel function by creating a `local_accessor`.

The `local_accessor` is created by specifying a `range` which is the number of
elements to allocate.

Note that local memory is allocated per work-group and each work-group can only
access its own local memory.

### 2.) Cache global memory access in local memory

Cache the global memory required for each work-group in local memory by reading
from global `accessor` and then writing to the local `accessor`.

Then write from the local accessor to the global memory output accessor in a
coalesced fashion.

Compare the performance with local memory and without local memory.
