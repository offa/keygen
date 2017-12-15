#!/bin/bash

set -ex


if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
fi


mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Release -DUNITTEST_VERBOSE=ON ..
make all
make unittest
make memcheck
make memcheck-test
