# SYCL Academy

## Exercise 17: Vectors
---

In this exercise you will learn how to use `vec` to explicitly vectorized your
kernel function.

---

### 1.) Use vectors

Now that global memory access is coalesced another optimization you can do is to
use the `vec` class to present the pixels in the image.

To do this first you want to reinterpret the `buffer` objects as `buffer`s with
the element type `float4`. You can do this by calling `reinterpret` on the
`buffer`s and specifying the type `float4`.

Note you will have to provide a new `range`s which will be the original `range`s
divided by 4 to account for the channels which are now represented by the four
elements of the vector type.

### 2.) Refactor the kernel function

Now that you are using vector types, you want to replace the representation of
pixels in the kernel function with a `float4` and remove any multiplication or
offsets to account for the number of channels.

## Build and execution hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
