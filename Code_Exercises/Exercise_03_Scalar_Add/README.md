# SYCL Academy

## Exercise 3: Scalar Add

---

In this exercise you will learn how to create `buffer`s to manage data and
`accessor`s to access the data within a kernel function.

---

### 1.) Allocate your input and output

Allocate memory on the host for your input and output data variables and assign
values to the inputs.

### 2.) Construct buffers

In SYCL buffers are used to manage data across the host and device(s).

Construct a buffer to manage your input and output data. The parameters to
construct a buffer are a pointer to the host data and a `1` dimensional `range`
of `1` to represent a single value. The element type and dimensionality can be
inferred from the pointer and the `range`.

### 3.) Construct accessors

In SYCL accessors are used to declare data dependencies to a SYCL kernel
function as well as to access the data within a SYCL kernel function.

Construct an accessor for each of the buffers to access the data of each within
the kernel function. The parameters to construct an `accessor` are the `buffer`
and the `handler`.

### 4.) Declare your kernel

Declare a SYCL kernel function using the `single_task` command provide a lambda
as the kernel function. The kernel function should use the `operator[]` of the
`accessor` objects to read from the inputs and write the sum to the output. As
each `accessor` is only accessing a single element you can simply specify `0`.

### 5.) Try a temporary buffer

You can construct a temporary `buffer` that doesn't copy back on destruction by
initializing it with just a `range` and no host pointer.

#### Build And Execution Hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpc.md).


For AdaptiveCpp: [instructions](../adaptivecp.md).
