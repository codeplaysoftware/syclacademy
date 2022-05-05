# SYCL Academy

## Exercise : Hello World

---

In this first exercise you will learn how to enqueue your first kernel function
to run on a device and print `Hello World!` to the console.

---

The purpose of this exercise is to compile some SYCL code.

Write some simple code using the examples in `source.cpp`.

Use the quick reference guide in `source.cpp` to output the device name
to `stdout`.

Extra fields may also be outputted using `get_info()`.

Try:

`sycl::info::device::version`
`sycl::info::device::driver_version`


#### Build And Execution Hints

In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.
There is a script provided in the folder for this exercise to compile and run your code. 

```sh
qsub -l nodes=1:gpu:ppn=2 -d . run.sh
```
Once the job has finished, in the same folder will be a file with a name similar to `run.sh.o1898955`
If you open this file you will see the program output from your SYCL code.

Refer to the [guide][devcloud-job-submission] for further information on the possibilities.

[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
