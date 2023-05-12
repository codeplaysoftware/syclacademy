# SYCL Academy

## Exercise : Hello World

---

In this first exercise you will learn how to enqueue your first kernel function
to run on a device and print `Hello World!` to the console.

---

The purpose of this exercise is to write a simple SYCL kernel.

Write some simple code using the hints in `source.cpp`.


#### Build And Execution Hints Using the DevCloud

For For DPC++:
```sh
icpx -fsycl -o sycl-ex-2 source.cpp
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.

We have provided a ready made script in the same directory as the source.cpp file, so you can call:

```sh
qsub -l nodes=1:gpu:ppn=2 -d . run.sh
```

For ComputeCpp:

```sh
cd ~/syclacademy/Code_Exercises/Exercise_02_Hello_World
compute++ source.cpp -lComputeCpp -sycl-driver -std=c++17 -DSYCL_LANGUAGE_VERSION=2020 -no-serial-memop
./a.out 
```

For hipSYCL:

```sh
syclcc -o sycl-ex-2 --hipsycl-targets="spirv" ../Code_Exercises/Exercise_02_Hello_World/source.cpp
./sycl-ex-2
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
