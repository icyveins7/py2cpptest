#include <gtest/gtest.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);

  // Start the interpreter!
  printf("Starting the python interpreter for GoogleTest...");
  py::scoped_interpreter guard{};
  printf("Done\n");

  return RUN_ALL_TESTS();
}
