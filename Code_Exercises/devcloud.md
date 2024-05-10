## Connect to Intel Developer Cloud via JupyterLab

* Start by creating an [Intel Developer Cloud][intel-devcloud] account if you do not already have one and login in.
* Go to [training](https://console.cloud.intel.com/training) and click on ```Launch JupyterLab´´´
* In the ```Jupiter Notebook``` select *File->New->Terminal*

## Building the Exercises with Intel oneAPI DPC++/C++ Compiler

* Execute the following command to download SYCL Academy project (if not already done):
```sh
git clone --recursive --branch isc24 https://github.com/codeplaysoftware/syclacademy.git
```
* To create the code_exercises directory structure with the Makefiles:
```sh
cd syclacademy
mkdir build
cd build
cmake ../ "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=ON -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```


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


