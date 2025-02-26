# ====================================================
# This is essentially the initialization
# It is assumed that if this is included, then all these
# are desired, and are set

set(PYBIND11_FINDPYTHON ON)
# This works as you would expect, assuming
# 1. activate your virtualenv
# 2. installed pybind11[global] (which copies to $VIRTUAL_ENV/share as well)
find_package(pybind11 CONFIG REQUIRED)

# We globally include and link the pybind stuff here, but you can change it
set(py2cpptest_INCLUDE_DIRS ${pybind11_INCLUDE_DIRS})
if (WIN32)
  set(py2cpptest_LIBRARIES pybind11::module pybind11::lto pybind11::windows_extras pybind11::embed)
else()
  set(py2cpptest_LIBRARIES pybind11::module pybind11::embed pybind11::lto)
endif()

set(py2cpptest_DIR ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest)

# ====================================================
# ================== BEGIN FUNCTIONS =================
# ====================================================
function(py2cpptest_add_target testname)
  target_link_libraries(${testname} PRIVATE ${py2cpptest_LIBRARIES})
  target_include_directories(${testname} PRIVATE
    ${py2cpptest_INCLUDE_DIRS}
    ${py2cpptest_DIR}/include
  )
endfunction()

# ====================================================
function(py2cpptest_add_py testname)
  foreach(FILE IN LISTS ARGN)
    # Strip leading subdirectory name
    get_filename_component(FILENAME ${FILE} NAME)

    add_custom_command(
      TARGET ${testname} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_SOURCE_DIR}/${FILE}
      ${CMAKE_BINARY_DIR}/${FILENAME}
    )
  endforeach()
endfunction()
