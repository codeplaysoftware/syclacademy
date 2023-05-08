#!/bin/bash
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling
icpx -fsycl -o image-convolution -I../../External/Catch2/single_include -I../../Utilities/include -I../../External/stb/ ./reference.cpp
if [ $? -eq 0 ]; then ./image-convolution; fi

