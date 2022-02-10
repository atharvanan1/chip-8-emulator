#! /bin/bash

cd `dirname $0`

curr_dir=`dirname $(realpath $0)`

cmake -S ${curr_dir} -B ${curr_dir}/build -DBUILD_TEST=OFF
cmake --build build
echo ""
echo "Program output:"
./build/src/Chip8Emu
