#!/bin/bash

set -ex

VALGRIND=false
SANITIZER=false # Disabled due to broken Clang (#71)
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
        -codeql)
            BUILD_ARGS=("-DCMAKE_BUILD_TYPE=Debug")
            SANITIZER=false
            ;;
    esac
done

apt-get update
apt-get install -y --no-install-recommends openssl libssl-dev valgrind python3-pip

pip3 install -U conan
conan profile new default --detect

if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
    conan profile update settings.compiler.libcxx=libc++ default
else
    conan profile update settings.compiler.libcxx=libstdc++11 default
fi



if [[ "${FLAWFINDER_ANALYSIS}" == true ]]
then
    apt-get install -y --no-install-recommends python3-pip
    pip3 install flawfinder
    flawfinder --error-level=1 src include
    exit
fi

if [[ "${SANITIZER}" == true ]]
then
    BUILD_ARGS+=("-DSANITIZER_ASAN=ON" "-DSANITIZER_UBSAN=ON")
fi


mkdir -p build && cd build

conan install \
    --build=missing \
    -g cmake_find_package \
    -g cmake_paths \
    -s compiler.cppstd=17 \
    ..


cmake -DCMAKE_TOOLCHAIN_FILE=./conan_paths.cmake "${BUILD_ARGS[@]}" ..
make
make unittest


if [[ "${VALGRIND}" == true ]]
then
    make memcheck
    make memcheck-test
fi
