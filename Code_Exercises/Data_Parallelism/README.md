# SYCL Academy

## Vector Add

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

#### 4.1 ) Use the `range` and `id` variant
This version of `parallel_for` takes a `range` specifying the number of
iterations of the kernel function to invoke and the kernel function itself must
take an `id` which represents the current iteration.

The `id` can be used in the `accessor` subscript operator to access or assign to
the corresponding element of data that the accessor represents.

#### 4.2 ) Use the `nd_range` and `nd_item` variant
This version of `parallel_for` takes an `nd_range` which is made up of two
`range`s describing the global range and the local range (work-group size). The
kernel function must take an `nd_item`, which cannot be passed directly to the
subscript operator of an `accessor`. Instead, retrieve the `id` using the
`get_global_id` member function.
