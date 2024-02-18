If you haven't done so already, use CMake to configure then build the exercises:
```sh
mkdir build
cd build
cmake .. "-GUnix Makefiles" -DSYCL_ACADEMY_USE_DPCPP=ON 
  -DSYCL_ACADEMY_ENABLE_SOLUTIONS=OFF -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx
```

To compile,from the syclacademy directory:
```sh
cd build/Code_Exercises/<Exercise directory>
make exercise_<exercise number>_source
```

Alternatively from a terminal at the command line:
```sh
icpx -fsycl -o exercise_<exercise number>_source -I../External/Catch2/single_include ../Code_Exercises/<Exercise directory>/source.cpp
```
