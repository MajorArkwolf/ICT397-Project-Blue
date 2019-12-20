#!/usr/bin/env bash

set -euxo pipefail

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
    set +x
    ./.travis/download-github-asset.sh opeik stonks vcpkg vcpkg.tar
    set -x

    mkdir -p "${VCPKG_ROOT}"
    tar -xf vcpkg.tar -C "${VCPKG_ROOT}"
    cd "${VCPKG_ROOT}"
    ./vcpkg.exe integrate install
fi

if [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
    brew install ${BREW_PACKAGES}
fi

git lfs install
