INCLUDE(FindPythonInterp)

SET(INTERNAL_NETCDF4_PYTHON ON)
SET(INTERNAL_CYTHON ON)


IF(INTERNAL_CYTHON)
  SET(CYTHON_URL "http://cython.org/release/Cython-0.17.1.tar.gz" CACHE STRING "URL to download Cython from")
ENDIF(INTERNAL_CYTHON)

IF(INTERNAL_NETCDF4_PYTHON)
  SET(NETCDF4_PYTHON_URL "http://netcdf4-python.googlecode.com/files/netCDF4-1.0.1.tar.gz" CACHE STRING "URL to download NetCDF4-python from")
ENDIF(INTERNAL_NETCDF4_PYTHON)





IF(INTERNAL_CYTHON)
  ExternalProject_Add(cython
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${CYTHON_URL}
    PREFIX ${BUILD_PREFIX}/cython-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${PYTHON_EXECUTABLE} setup.py build
    INSTALL_COMMAND ${PYTHON_EXECUTABLE} setup.py install --prefix=${CMAKE_BINARY_DIR}/ext_build/python
  ) 
  SET(PREV_PYTHON_BUILD ${PREV_PYTHON_BUILD} cython)
ENDIF(INTERNAL_CYTHON)


IF(INTERNAL_NETCDF4_PYTHON)
  SET(PYTHON_CPPFLAGS -I${NETCDF_INCLUDE_PATH})
  SET(PYTHON_LDFLAGS -L${NETCDF_BIN_DIR}/lib)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
           "-DPYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}"
           "-DPYTHON_CPPFLAGS:STRING=${PYTHON_CPPFLAGS}"
           "-DHDF5_DIR=${HDF5_BIN_DIR}"
           "-DNETCDF4_DIR=${NETCDF_BIN_DIR}"
           "-DPYTHON_LDFLAGS:STRING=${PYTHON_LDFLAGS}"
           "-DTARGET_PATH=${CMAKE_BINARY_DIR}/ext_build/python" "-P") 

  ExternalProject_Add(netcdf4-python
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${NETCDF4_PYTHON_URL}
    PREFIX ${BUILD_PREFIX}/netcdf4-python-prefix
    CONFIGURE_COMMAND echo "No configure" 
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT}  ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  )
ENDIF(INTERNAL_NETCDF4_PYTHON)


execute_process(
   COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/external/detect_site.py ${CMAKE_BINARY_DIR}/ext_build/python
   RESULT_VARIABLE RET_VALUE
   OUTPUT_VARIABLE PYTHON_LOCAL_SITE_PACKAGE
)
IF(RET_VALUE)
  MESSAGE(FATAL_ERROR "Could not detect the location of site-package in the build directory")
ENDIF(RET_VALUE)

MESSAGE(STATUS "Python is installing its packages in ${PYTHON_LOCAL_SITE_PACKAGE}") 
