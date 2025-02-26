#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include "general.h"

#include <vector>
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

  std::vector<double> x = {1.0, 2.0, 3.0};
  std::vector<double> y = {1.0, 4.0, -1.0};
  auto result2 = pct::runPythonFunction(
    "module1", "addarrs",
    pct::toNumpyArray(x), pct::toNumpyArray(y)
  );
  py::print(py::str(result2));

  // Convert the output to an std vector
  py::array_t<double, py::array::c_style | py::array::forcecast> randresult = pct::runPythonFunction("module2", "rand", 5);
  std::vector<double> stdrandresult = pct::fromNumpyArray(randresult);
  for (auto i : stdrandresult){
    std::cout << i << " ";
  }
  std::cout << std::endl;

  py::array_t<double, py::array::c_style | py::array::forcecast> anotherrandresult = pct::runPythonFunction("numpy", "random.randn", 6);
  std::vector<double> stdanotherrandresult = pct::fromNumpyArray(anotherrandresult);
  for (auto i : stdanotherrandresult){
    std::cout << i << " ";
  }


  return 0;
}
