#! /bin/bash

cd `dirname $0`
cmake -S . -B build
cmake --build build
pushd build
ctest
popd
