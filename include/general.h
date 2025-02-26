#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/numpy.h>

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


/**
 * @brief Strictly converts a NumPy array to an std::vector of the same type.
 *
 * @tparam T Type of elements
 * @param input Input NumPy array; forced to be densely packed C-style
 * @return Output std::vector
 */
template <typename T>
py::array_t<T, py::array::c_style | py::array::forcecast> toNumpyArray(
  const std::vector<T>& input
){
  py::array_t<T, py::array::c_style | py::array::forcecast> output(input.size());
  auto outputProxy = output.mutable_unchecked();
  std::copy(input.begin(), input.end(), outputProxy.mutable_data());
  return output;
}

/**
 * @brief Strictly converts a NumPy array to an std::vector of the same type.
 *
 * @tparam T Type of elements
 * @param input Input NumPy array; forced to be densely packed C-style
 * @return Output std::vector
 */
template <typename T>
std::vector<T> fromNumpyArray(
  const py::array_t<T, py::array::c_style | py::array::forcecast>& input
){
  auto inputProxy = input.unchecked();
  std::vector<T> output(inputProxy.size());
  std::copy(inputProxy.data(), inputProxy.data() + inputProxy.size(), output.begin());
  return output;
}



}
