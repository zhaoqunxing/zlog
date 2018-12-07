add_executable (zlogTest zlogTest.cpp)
add_dependencies(zlogTest zlog)
target_link_libraries(zlogTest zlog)
