#!/bin/bash

set -ex

VALGRIND=false
SANITIZER=true
FLAWFINDER_ANALYSIS=false

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
    apt-get install -y flawfinder

    flawfinder --version
    flawfinder src include
    exit 0
fi


if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
fi

if [[ "${SANITIZER}" == true ]]
then
    BUILD_FLAGS="-DSANITIZER_ASAN=ON -DSANITIZER_UBSAN=ON"
fi


mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Debug \
        ${BUILD_FLAGS} \
        ..
make all
make unittest


if [[ "${VALGRIND}" == true ]]
then
    make memcheck
    make memcheck-test
fi
