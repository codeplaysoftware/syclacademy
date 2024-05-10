# SYCL Academy

## Image Convolution (implementation with functors)
---

In this exercise you will learn how to use `functors` instead of lambda
functions as kernels.

---

### 1.) Use functors

Now that global memory access is coalesced and optimized using `vec`, you can
further optimize by using a linear buffer. Given that the blur filter is
symmetrical, the same result can be achieved by applying the same linear filter
to rows and columns. Instead of using a lambda function for the kernel, a
functor, which can be reused, is preferable.

To implement this, you need to create a functor class that accepts an input
accessor, an output accessor, an accessor containing the linear filter, and a
parameter that specifies the direction in which the filter will be applied.

Keep in mind that in order to apply the linear filter twice, an intermediate
buffer of the same size as the input buffer is required to hold the result of
the first pass.

### 2.) Refactor the kernel function

The kernel function must consider both the direction in which the filter needs
to be applied and the necessity to store the intermediate image while
preserving the halo. It's important to note that the halo is not required for
the final image.

## Build and execution hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
