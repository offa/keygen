#!/bin/bash

set -ex

VALGRIND=false
SANITIZER=true
FLAWFINDER_ANALYSIS=false
BUILD_ARGS=()
BUILD_TYPE=Release

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
            BUILD_TYPE=Debug
            SANITIZER=false
            ;;
    esac
done

export DEBIAN_FRONTEND=noninteractive
export PATH=$HOME/.local/bin:$PATH
apt-get update
apt-get install -y --no-install-recommends openssl libssl-dev valgrind pipx

pipx install conan
conan profile detect

if [[ "${CXX}" == clang* ]]
then
    export CXXFLAGS="-stdlib=libc++"
    sed -i 's/^compiler.libcxx=.*$/compiler.libcxx=libc++/g' ~/.conan2/profiles/default
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
    -s compiler.cppstd=17 \
    -s build_type=${BUILD_TYPE} \
    ..


cmake -DCMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" "${BUILD_ARGS[@]}" ..
make
make unittest


if [[ "${VALGRIND}" == true ]]
then
    make memcheck
    make memcheck-test
fi
