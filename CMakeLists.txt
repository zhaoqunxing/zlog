cmake_minimum_required (VERSION 2.8)

project (zlog)

set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set (CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


add_subdirectory (zlog bin/zlog)
add_subdirectory (test bin/test)


