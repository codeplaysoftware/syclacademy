# SYCL Academy

## Exercise 18: Local Memory Tiling
---

In this exercise you will learn how to cache global memory into local memory in
tiles according to work-groups in order to compare the performance difference. 

---

### 1.) Use local memory

Allocate local memory for the kernel function by creating a local `accessor`.

The local `accessor` is created by specifying a `range` which is the number of
elements to allocate.

Note that local memory is allocated per work-group and each work-group can only
access it's own local memory.

### 2.) Cache global memory access in local memory

Cache the global memory required for each work-group in local memory by reading
from global `accessor` and then writing to the local `accessor`.

Remember to use the local id to know where in local memory to store the data,
this can be queried by calling the `nd_item` member function `get_local_id`.

Compare the performance with local memory and without local memory.

## Build and execution hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpc.md).

For AdaptiveCpp: [instructions](../adaptivecp.md).