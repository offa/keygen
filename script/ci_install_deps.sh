#!/bin/bash

set -ex

BUILD_DIR=${TRAVIS_BUILD_DIR}

mkdir -p "${DEPENDENCY_DIR}" && cd "${DEPENDENCY_DIR}"


# --- CppUTest
if [[ ! -d "${DEPENDENCY_DIR}/cpputest" ]]
then
    git clone --depth=1 https://github.com/cpputest/cpputest.git cpputest
fi

cd cpputest

BUILD_FLAGS="-DC++11=ON -DTESTS=OFF"

if [[ "$CXX" == clang* ]]
then
    BUILD_FLAGS="${BUILD_FLAGS} -DCMAKE_CXX_FLAGS=-stdlib=libc++"
fi

mkdir -p _build-${CC} && cd _build-${CC}
cmake ${BUILD_FLAGS} ..
make -j4 && sudo make install

cd ${DEPENDENCY_DIR}

