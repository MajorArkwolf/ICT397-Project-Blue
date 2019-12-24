#!/usr/bin/env bash

set -euxo pipefail

build_args=' -D CMAKE_BUILD_TYPE="Debug" -D DisablePostBuild:BOOL=ON '

if [[ "${TRAVIS_EVENT_TYPE}" == "pull_request" ]]; then
    build_args+=' WarningsAsErrors:BOOL=ON '
fi

if [[ "${TRAVIS_OS_NAME}" == "linux" ]] || [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
    mkdir -p build
    cd build
    cmake ${build_args} ..
    VERBOSE=1 cmake --build .
fi

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
    mkdir -p build
    cd build
    cmake ${build_args} -D CMAKE_GENERATOR_PLATFORM=x64 \
        -D CMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
        -D VCPKG_TARGET_TRIPLET=x64-windows ..

    cmake --build .
fi
