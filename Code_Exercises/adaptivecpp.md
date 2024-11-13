If you haven't done so already, use CMake to configure then build the exercises:
```sh
# <target specification> is a list of backends and devices to target, for example
# "generic" compiles for CPUs and GPUs using the generic single-pass compiler.
# When in doubt, use "generic" as it usually generates the fastest binaries.
#
# Recent, full installations of AdaptiveCpp may not need targets to be provided,
# compiling for "generic" by default.
cmake -DSYCL_ACADEMY_USE_ADAPTIVECPP=ON -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF
-DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/adaptivecpp -DACPP_TARGETS="<target specification>" ..
```

To compile,from the syclacademy directory:
```sh
cd build/Code_Exercises/<Exercise directory>
make <exercise name>_source
```
 
alternatively, without CMake:
```sh
cd Code_Exercises/<Exercise directory>
/path/to/adaptivecpp/bin/acpp -o sycl-<exercise name>_source --acpp-targets="<target specification>" source.cpp
./sycl-<exercise name>_source
```
