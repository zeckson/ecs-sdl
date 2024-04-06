# !/bin/sh

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=g++ -G Ninja -S . -B build/debug
