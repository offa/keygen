#!/bin/bash

set -ex


## Install CppUTest
CPPUTEST_VERSION=master
BUILD_FLAGS="-DC++11=OFF -DTESTS=OFF"

if [[ "$CXX" == clang* ]]; then
    BUILD_FLAGS="$BUILD_FLAGS -DCMAKE_CXX_FLAGS=-stdlib=libc++" 
fi

wget https://github.com/cpputest/cpputest/archive/${CPPUTEST_VERSION}.tar.gz
tar -xzf ${CPPUTEST_VERSION}.tar.gz
pushd cpputest-${CPPUTEST_VERSION}
mkdir _build && cd _build
cmake $BUILD_FLAGS ..
make -j4 && sudo make install
popd

