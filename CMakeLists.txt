cmake_minimum_required(VERSION 3.18)

project(py2cpptest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Demonstration of initialization
include(unittest.cmake)

# Demonstration of included functions and embedding interpreter
add_executable(example_embed src/example_embed.cpp)
py2cpptest_add_target(example_embed)
py2cpptest_add_py(example_embed src/module1.py src/module2.py)

# Demonstration of test with GoogleTest
if (GTest_FOUND)
  message("====== GTest found; building GTest example!")

  enable_testing()
  add_executable(example_gtest src/example_gtest.cpp)
  target_link_libraries(example_gtest PRIVATE GTest::gtest)
  py2cpptest_add_target(example_gtest)
  py2cpptest_add_py(example_gtest src/module1.py src/module2.py)

  include(GoogleTest)
  gtest_discover_tests(example_gtest)
endif()

