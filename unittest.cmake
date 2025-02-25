# ====================================================
function(py2cpptest_init)
  set(PYBIND11_FINDPYTHON ON)
  # This works as you would expect, assuming
  # 1. activate your virtualenv
  # 2. installed pybind11[global] (which copies to $VIRTUAL_ENV/share as well)
  find_package(pybind11 CONFIG REQUIRED)

  # We globally include and link the pybind stuff here, but you can change it
  set(py2cpptest_INCLUDE_DIRS ${pybind11_INCLUDE_DIRS} PARENT_SCOPE)
  if (WIN32)
    set(py2cpptest_LIBRARIES pybind11::module pybind11::lto pybind11::windows_extras PARENT_SCOPE)
  else()
    set(py2cpptest_LIBRARIES pybind11::module pybind11::lto PARENT_SCOPE)
  endif()
endfunction()

# ====================================================
function(py2cpptest_add_test testname)
  target_link_libraries(test PRIVATE ${py2cpptest_LIBRARIES})
  target_include_directories(test PRIVATE ${py2cpptest_INCLUDE_DIRS})
endfunction()
