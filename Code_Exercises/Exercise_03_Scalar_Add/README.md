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
