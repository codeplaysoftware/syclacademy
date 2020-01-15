# Parallelism in Modern C++; from CPU to GPU
### Exercise 5: Transpose

---

In this first exercise you will learn:
* How to create a simple matrix transpose kernel.
* How to allocate and use local memory.
* How to synchronize work-groups.
* How different work-group sizes effect performance.

---

Matrix transpose is a very useful operation when working in linear algebra applications and can be performed efficiently on a GPU.

A matrix transpositions switches the dimensions of a matrix, for example:

```
A = [1, 2, 3]  =>  A` = [1, 4, 7]
    [4, 5, 6]           [2, 5, 8]
    [7, 8, 9]           [3, 6, 9]
```

1.) Write a SYCL kernel for transposing matrices

For the purposes of this exercise the source file provides a stub that defines a simple matrix class, whose data can be retrieved using the `data` member function and can be printed for evaluating the results using the `print` member function. Note for representation purposes `print` will display in row-major linearization.

Define a SYCL kernel function that takes an input matrix and an output matrix, and assigns the elements of the input the transposed position in the output. As a hint try calculating the the row-major and column-major liniearizations of the `id`.

It's recommended that you use a 2-dimensional `range` for the `parallel_for`.

Try observing that no matter how you change the linearization the performance will be largely unaffected.

2.) Use local memory to improve global memory coalescing

Create a local `accessor` (an `accesor` with the `access::target::local` access target), remember a local `accessor` must have the `access::mode::read_write` access mode. The constructor the local `accessor` just takes a `range` specifying the number of elements to allocate per work-group and the `handler`.

Once you've created an accessor pass it to the SYCL kernel function as you did the buffer `accessor`s. You can then copy the elements of global memory from the buffer `accessor` to local memory in the local `accessor`.

Make sure to read coalesce the reads from global memory and then assign into local memory already transposed so that the writes to global memory can also be coalesced.

You should be able to observe a performance gain from doing this.

3.) Try different work-group sizes

Try using different work-group sizes for you SYCL kernel function. Remember you will have to specify an `nd_range` in order to specify the local range.

Work-group sizes you could try are 8x8, 16x16, 16x32. Note that some of these may not work if your GPU does not support work-groups that large.

Remember you can query the maximum work-group size using the `device` class' `get_info` member function.
