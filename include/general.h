#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

namespace pct
{

/**
 * @brief Runs a specified python function from a specified python module.
 *
 * @tparam Args Variadic argument types
 * @param moduleName Python module file name
 * @param functionName Python function name
 * @param args Arguments to pass to the python function
 * @return py::object result
 */
template <typename... Args>
py::object runPythonFunction(
  const char *moduleName,
  const char *functionName,
  Args... args
){
  py::module module = py::module::import(moduleName);
  py::object func = module.attr(functionName);
  return func(args...);
}


template <typename... Args>
py::object runPythonFunctionWithInterpreter(
  const char *moduleName,
  const char *functionName,
  Args... args
){
  py::scoped_interpreter guard{};
  return runPythonFunction(moduleName, functionName, args...);
}



}
