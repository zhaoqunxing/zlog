#!/bin/bash

export CXXFLAGS=-m32  
export CFLAGS=-m32

rm -rf build
mkdir build
  && cd build \
  && cmake .. -DCMAKE_BUILD_TYPE=Debug \
  && cmake --build . \
