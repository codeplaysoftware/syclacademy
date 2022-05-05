#!/bin/bash
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling
dpcpp -o nd-range ./source.cpp
if [ $? -eq 0 ]; then ./nd-range; fi