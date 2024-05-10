## Compiling with DPC++

From the syclacademy directory
```sh
cd build/Code_Exercises/<Exercise directory>
```
and execute:
* ```make <exercise name>_source``` - to build source.cpp
* ```make <exercise name>_solution``` - to build the solution provided
* ```make``` - to build both

Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o <exercise name>_source -I../External/Catch2/single_include ../Code_Exercises/<Exercise directory>/source.cpp
```

In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only available through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission`
```sh
#!/bin/bash
./<exercise name>_source
```
and run:
```sh
qsub -l nodes=1:gpu:ppn=2 -d . job_submission
```

The stdout will be stored in ```job_submission.o<job id>``` and stderr in ```job_submission.e<job id>```.

[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
