#!/bin/sh

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=g++ -G Ninja -S . -B build/release
