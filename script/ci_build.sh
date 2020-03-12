#!/bin/bash

set -ex

VALGRIND=false
SANITIZER=true
FLAWFINDER_ANALYSIS=false
BUILD_ARGS=("-DCMAKE_BUILD_TYPE=Release")

for arg in "$@"
do
    case "${arg}" in
        -valgrind)
            VALGRIND=true
            SANITIZER=false
            ;;
        -no-san)
            SANITIZER=false
            ;;
        -flawfinder)
            FLAWFINDER_ANALYSIS=true
            ;;
    esac
done


if [[ "${FLAWFINDER_ANALYSIS}" == true ]]
then
    apt-get install -y --no-install-recommends python3-pip
    pip3 install flawfinder
    flawfinder --error-level=1 src include
    exit
fi


if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
fi

if [[ "${SANITIZER}" == true ]]
then
    BUILD_ARGS+=("-DSANITIZER_ASAN=ON" "-DSANITIZER_UBSAN=ON")
fi


mkdir -p build && cd build

cmake "${BUILD_ARGS[@]}" ..
make
make unittest


if [[ "${VALGRIND}" == true ]]
then
    make memcheck
    make memcheck-test
fi
