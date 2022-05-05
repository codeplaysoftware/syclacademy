# SYCL Academy

## Exercise : Hello World

---

In this first exercise you will learn how to enqueue your first kernel function
to run on a device and print `Hello World!` to the console.

---

The purpose of this exercise is to compile some SYCL code.

Write a simple code using the examples in `source.cpp` and compile with

```
dpcpp -o hello-world source.cpp
```

Try to run the code using 
```
./hello-world
```

Use the quick reference guide in `source.cpp` to output the device name
to `stdout`.

Extra fields may also be outputted using `get_info()`.

Try:

`sycl::info::device::version`
`sycl::info::device::driver_version`


#### Build And Execution Hints

In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:
```sh
qsub job_submission
```

[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
