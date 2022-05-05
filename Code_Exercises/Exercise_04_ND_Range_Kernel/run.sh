#!/bin/bash
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling
dpcpp solution.cpp
if [ $? -eq 0 ]; then ./a.out; fi

