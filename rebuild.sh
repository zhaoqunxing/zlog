#!/bin/bash
if [[ $1 == 0 ]]; then
    rm -rf build
    mkdir build && cd build && cmake .. && make
else
    cd build && make clean && make
fi
