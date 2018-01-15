#!/bin/bash

set -ex

VALGRIND=false
SANITIZER=true

for arg in "$@"
do
    case "${arg}" in
        -valgrind)
            VALGRIND=true
            SANITIZER=false
            ;;
    esac
done


if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"

    # Clang's sanitizer conflict with CppUTest's Leakdetection (see #18)
    # Instead of ASan / UBSan, Valgrind is used later in the build
    VALGRIND=true
    SANITIZER=false
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
