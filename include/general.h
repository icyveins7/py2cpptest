#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/numpy.h>

#include <cstring>
#include <string>

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
  // Module is independent
  py::module module = py::module::import(moduleName);

  // Turn into an std::string so we can parse it more easily
  const std::string str(functionName);
  const char delimiter = '.';

  // For simple cases like np.arange
  if (str.find(delimiter) == std::string::npos)
    return module.attr(functionName)(args...);

  // For more complicated cases like np.random.rand
  // Place random.rand into functionName
  size_t start = 0;
  size_t end = str.find(delimiter);

  // This is the first part
  // NOTE: we do this because we can't seem to cast module to object?
  // printf("%s\n", str.substr(start, end - start).c_str()); // debug
  py::object func = module.attr(str.substr(start, end - start).c_str());
  start = end + 1;
  end = str.find(delimiter, start);

  // This is the rest of the parts
  do {
    // printf("do: %s, %zd, %zd\n", str.substr(start, end - start).c_str(), start, end); // debug
    func = func.attr(str.substr(start, end - start).c_str());

    if (end == std::string::npos)
      break;

    start = end + 1;
    end = str.find(delimiter, start);
  } while (end != std::string::npos);

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
