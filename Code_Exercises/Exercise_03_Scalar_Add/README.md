# SYCL Academy

## Exercise 3: Scalar Add using Buffers and USM

---

In this exercise you will learn how to create `buffer`s to manage data and
`accessor`s to access the data within a kernel function. 

You'll then use the USM functions `malloc_device`, `fill` and `memcpy` to 
allocate some memory on the device, fill it, copy it back, and free the 
device allocation.

---

## Buffers 

## Instructions

1. Initialize 2 buffers to point to ints a, b.
2. Use another `single_task` within another q.submit to add `a` and `b` 
together and store the value in `a`.
3. Allow the buffers to destruct and check that `a` contains the correct answer.


## USM

1. Allocate an int on device.
2. Fill the int.
3. Memcpy the int back to host memory.
4. Free the allocated int.

Remember that fill() and mempcy() are asynchronous, so make
sure you `wait()` between fill() and memcpy() or else you
aren't guaranteed to get the expected result.


#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):

```sh
dpcpp -o sycl-ex-3 ../Code_Exercises/Exercise_03_Scalar_Add/source.cpp

./sycl-ex-3
```

In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:

```sh
qsub job_submission
```



[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
