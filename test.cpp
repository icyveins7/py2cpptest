#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
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
  py::module module1 = py::module::import("module1");
  py::object arange = module1.attr("arange");
  py::object result = arange(0, 3);
  py::print(py::str(result));

  py::module module2 = py::module::import("module2");
  py::object rand = module2.attr("rand");
  py::object randresult = rand(5);
  py::print(py::str(randresult));

  return 0;
}
