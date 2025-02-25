#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include "general.h"

#include <iostream>

namespace py = pybind11;

int main(){
  // Starts interpreter, RAII
  py::scoped_interpreter guard{};

  // Import and use an in-built module
  py::module sys = py::module::import("sys");
  py::print(py::str(sys.attr("executable")));

  // Import and use an installed pip module
  py::module np = py::module::import("numpy");
  py::print(py::str(np.attr("arange")(0, 10)));

  // Import and use a custom module .py
  // Note that this only works if the .py file is in the
  // current working directory.
  // This is not the case if you just cmake a project,
  // since the .py file is probably not copied to the build folder
  auto result = pct::runPythonFunction("module1", "arange", 0, 3);
  py::print(py::str(result));

  auto randresult = pct::runPythonFunction("module2", "rand", 5);
  py::print(py::str(randresult));

  return 0;
}
