#!/bin/bash

set -ex


if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
fi


mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Debug \
        -DUNITTEST_VERBOSE=ON \
        -DSANITIZER_ASAN=ON \
        -DSANITIZER_UBSAN=ON \
        ..
make all
make unittest
