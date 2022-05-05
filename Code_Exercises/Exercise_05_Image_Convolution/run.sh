#!/bin/bash
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling
dpcpp -o image-convolution ./reference.cpp
if [ $? -eq 0 ]; then ./image-convolution; fi