#include <gtest/gtest.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "general.h"

namespace py = pybind11;

template <typename T>
using numpy_array = py::array_t<T, py::array::c_style | py::array::forcecast>;

TEST(ExampleGTest, Arange){
  numpy_array<int64_t> x = pct::runPythonFunction("module1", "arange", 0, 3);
  std::vector<int64_t> xc = pct::fromNumpyArray(x);

  std::vector<int64_t> y = {0, 1, 2};

  for (size_t i = 0; i < xc.size(); i++){
    EXPECT_EQ(xc[i], y[i]);
  }

}

TEST(ExampleGTest, AddArrs){
  std::vector<float> x = {1.0, 2.0, 3.0};
  std::vector<float> y = {1.0, 4.0, -1.0};
  numpy_array<float> z = pct::runPythonFunction("module1", "addarrs", pct::toNumpyArray(x), pct::toNumpyArray(y));

  std::vector<float> zc = pct::fromNumpyArray(z);
  std::vector<float> expected = {2.0, 6.0, 2.0};

  for (size_t i = 0; i < zc.size(); i++){
    EXPECT_EQ(zc[i], expected[i]);
  }
}
