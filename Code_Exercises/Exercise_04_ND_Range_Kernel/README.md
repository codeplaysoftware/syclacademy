## Exercise: ND Range Kernel
---

In this exercise you will learn how to enqueue ND range kernel functions.

---

### 1.) Use items in parallel_for

Using the application from any exercise so far or creating a new one, enqueue a
kernel function using the `parallel_for` variant which takes a `range` but has
the kernel function take an `item`.

Feel free to use either the buffer/accessor model and feel free to use any
method of synchronization and copy back.

When using an `item` you cannot pass this directly to the subscript operator of
an `accessor` you have to retrieve the `id`, you can do this by calling the
`get_id` member function.

### 2.) Enqueue an ND range kernel

Using the application from any exercise so far or creating a new one, enqueue an
ND range kernel function using the `parallel_for` variant which takes an
`nd_range`.

Remember an `nd_range` is made up of two `range`s, the first being the global
range and the second being the local range or the work-group size.

Remember that when using this variant of `parallel_for` the kernel function
takes an `nd_item`.

Similarly to to the `item` when using the `nd_item` you cannot pass this
directly to the subscript operator of an `accessor`, you can retrieve the `id`
by calling the `get_global_id` member function.

Feel free to use either the buffer/accessor model and feel free to use any
method of synchronization and copy back.

#### Build And Execution Hints Using the DevCloud

For For DPC++:
```sh
icpx -fsycl -o sycl-ex-4 source.cpp
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.

We have provided a ready made script in the same directory as the source.cpp file, so you can call:

```sh
./q run.sh
```

For ComputeCpp:

```sh
cd ~/syclacademy/Code_Exercises/Exercise_04_ND_Range_Kernel
compute++ source.cpp -lComputeCpp -sycl-driver -std=c++17 -DSYCL_LANGUAGE_VERSION=2020 -no-serial-memop
./a.out 
```



For hipSYCL:

```sh
syclcc -o sycl-ex-1 --hipsycl-targets="spirv" ../Code_Exercises/Exercise_04_ND_Range_Kernel/source.cpp
./sycl-ex-4
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
