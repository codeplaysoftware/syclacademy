# SYCL Academy

## Exercise 6: Vector Add

---

In this exercise you will learn how add the values in two arrays and write the
results to another array in parallel using `parallel_for`.

---

### 1.) Create your queue

Create a `queue` to enqueue your kernel function to, remember to handle errors.

### 2. ) Create buffers

Create `buffer`s to manage the data of the two input arrays and output array.

Remember to ensure the `range` provided to the buffer is the size of the arrays.

### 3. ) Create accessors

Create `accessor`s to each of the `buffer`s within the command group function.

### 4. ) Write the kernel function

Now enqueue parallel kernel function by calling `parallel_for` on the `handler`.

This function takes a `range` specifying the number of iterations of the kernel
function to invoke and the kernel function itself must take an `id` which
represents the current iteration.

The `id` can be used in the `accessor` subscript operator to access or assign to
the corresponding element of data that the accessor represents.


#### Build And Execution Hints

For DevCloud via SSH follow these [instructions](../devcloud.md).

For DPC++: [instructions](../dpcpp.md).

For AdaptiveCpp: [instructions](../adaptivecpp.md).
