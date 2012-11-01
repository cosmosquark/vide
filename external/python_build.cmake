SET(ENV{HDF5_DIR} ${HDF5_DIR})
SET(ENV{NETCDF4_DIR} ${NETCDF4_DIR})
SET(ENV{CPPFLAGS} ${PYTHON_CPPFLAGS})
SET(ENV{LDFLAGS} ${PYTHON_LDFLAGS})
SET(ENV{PYTHONPATH} ${TARGET_PATH}/lib/python2.7/site-packages:$ENV{PYTHONPATH})
execute_process(
  COMMAND ${PYTHON_EXECUTABLE} setup.py build
  RESULT_VALUE RET_VALUE
)

IF(NOT RET_VALUE EQUAL 0)
  MESSAGE(FATAL_ERROR "Error in python build")

ENDIF(NOT RET_VALUE EQUAL 0)

