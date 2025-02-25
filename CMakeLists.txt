cmake_minimum_required(VERSION 3.18)

project(py2cpptest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Demonstration of initialization
include(unittest.cmake)

# Demonstration of adding a test
add_executable(test src/test.cpp)
py2cpptest_add_target(test)
py2cpptest_add_py(test src/module1.py src/module2.py)

