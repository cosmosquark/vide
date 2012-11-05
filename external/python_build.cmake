SET(ENV{HDF5_DIR} ${HDF5_DIR})
SET(ENV{NETCDF4_DIR} ${NETCDF4_DIR})
SET(ENV{CPPFLAGS} ${PYTHON_CPPFLAGS})
SET(ENV{LDFLAGS} ${PYTHON_LDFLAGS})
SET(ENV{VOID_GSL} ${VOID_GSL})
SET(ENV{PYTHONPATH} ${PYTHON_LOCAL_SITE_PACKAGE}:$ENV{PYTHONPATH})
SET(PYTHON_BUILD_COMMAND ${PYTHON_EXECUTABLE} setup.py build)
MESSAGE(STATUS "Running ${PYTHON_BUILD_COMMAND}")
execute_process(
  COMMAND ${PYTHON_BUILD_COMMAND}
  RESULT_VARIABLE RET_VALUE
)

IF(NOT RET_VALUE EQUAL 0)
  MESSAGE(FATAL_ERROR "Error in python build")

ENDIF(NOT RET_VALUE EQUAL 0)

