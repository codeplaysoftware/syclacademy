## Using Intel Developer Cloud via JupyterLab

If you haven't done so already, follow this [guide](../README.md#connect-to-intel-developer-cloud-via-jupyterlab) to build the exercise directory structure.

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
icpx -fsycl -o <exercise name>_source -I../../External/Catch2/single_include ../Code_Exercises/<Exercise directory>/source.cpp
```

To execute just run:

```sh
./<exercise name>_source
```
