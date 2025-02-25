cmake_minimum_required(VERSION 3.18)

project(py2cpptest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Demonstration of initialization
include(unittest.cmake)
py2cpptest_init()

# Demonstration of adding a test
add_executable(test test.cpp)
py2cpptest_add_test(test)

