SET(ENV{HDF5_DIR} ${HDF5_DIR})
SET(ENV{NETCDF4_DIR} ${NETCDF4_DIR})
SET(ENV{CPPFLAGS} ${PYTHON_CPPFLAGS})
SET(ENV{LDFLAGS} ${PYTHON_LDFLAGS})
SET(ENV{VOID_GSL} ${VOID_GSL})
SET(ENV{CFITSIO_EXT_INC} ${CFITSIO_EXT_INC})
SET(ENV{CFITSIO_EXT_PREFIX} ${CFITSIO_EXT_PREFIX})
SET(ENV{CFITSIO_EXT_LIB} ${CFITSIO_EXT_LIB})
SET(ENV{PYTHONPATH} ${PYTHON_LOCAL_SITE_PACKAGE}:$ENV{PYTHONPATH})
SET(ENV{CC} ${CMAKE_C_COMPILER})
SET(ENV{CXX} ${CMAKE_CXX_COMPILER})


SET(PYTHON_INSTALL_COMMAND ${PYTHON_EXECUTABLE} setup.py install --prefix=${TARGET_PATH} --install-lib=${PYTHON_LOCAL_SITE_PACKAGE})

message(STATUS "Running ${PYTHON_INSTALL_COMMAND}")
execute_process(
  COMMAND ${PYTHON_INSTALL_COMMAND}
  RESULT_VARIABLE RET_VALUE
)

IF(NOT ${RET_VALUE} EQUAL 0)
  MESSAGE(FATAL_ERROR "Error in python install")
ENDIF(NOT ${RET_VALUE} EQUAL 0)
