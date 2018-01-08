#!/bin/bash

set -ex

if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
    # Clang's sanitizer conflict with CppUTest's Leakdetection (see #18)
    # Instead of ASan / UBSan, Valgrind is used later in the build
else
    BUILD_FLAGS_SANITIZER="-DSANITIZER_ASAN=ON DSANITIZER_UBSAN=ON"
fi


mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Debug \
        -DUNITTEST_VERBOSE=ON \
        ${BUILD_FLAGS_SANITIZER} \
        ..
make all
make unittest


if [[ "${CXX}" == clang* ]]
then
    make memcheck
    make memcheck-test
fi
