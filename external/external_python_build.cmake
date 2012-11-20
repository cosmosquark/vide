INCLUDE(FindPythonInterp)

SET(INTERNAL_NETCDF4_PYTHON ON)
SET(INTERNAL_CYTHON ON)
SET(INTERNAL_HEALPY ON)

IF (PYTHON_VERSION_STRING VERSION_LESS 2.7)
  MESSAGE(STATUS "Python version is less than 2.7, argparse is needed.")
  SET(INTERNAL_ARGPARSE ON)
ELSE (PYTHON_VERSION_STRING VERSION_LESS 2.7)
  MESSAGE(STATUS "Python version is greater than 2.7, argparse is already bundled.")
ENDIF (PYTHON_VERSION_STRING VERSION_LESS 2.7)

IF(INTERNAL_CYTHON)
  SET(CYTHON_URL "http://cython.org/release/Cython-0.17.1.tar.gz" CACHE STRING "URL to download Cython from")
  mark_as_advanced(CYTHON_URL)
ENDIF(INTERNAL_CYTHON)

IF(INTERNAL_NETCDF4_PYTHON)
  SET(NETCDF4_PYTHON_URL "http://netcdf4-python.googlecode.com/files/netCDF4-1.0.1.tar.gz" CACHE STRING "URL to download NetCDF4-python from")
  mark_as_advanced(NETCDF4_PYTHON_URL)
ENDIF(INTERNAL_NETCDF4_PYTHON)

IF (INTERNAL_HEALPY)
  SET(HEALPY_URL "http://github.com/healpy/healpy/archive/1.4.1.tar.gz" CACHE STRING "URL to download Healpy from")
  mark_as_advanced(HEALPY_URL)
ENDIF(INTERNAL_HEALPY)

IF(INTERNAL_ARGPARSE)
  SET(SETUPTOOLS_URL "http://pypi.python.org/packages/source/s/setuptools/setuptools-0.6c11.tar.gz" CACHE STRING "URL to download setuptools from")
  SET(ARGPARSE_URL "http://argparse.googlecode.com/files/argparse-1.2.1.tar.gz" CACHE STRING "URL to download argparse from")
  mark_as_advanced(ARGPARSE_URL SETUPTOOLS_URL)
ENDIF(INTERNAL_ARGPARSE)

execute_process(
   COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/external/detect_site.py ${CMAKE_BINARY_DIR}/ext_build/python
   RESULT_VARIABLE RET_VALUE
   OUTPUT_VARIABLE PYTHON_LOCAL_SITE_PACKAGE
)
IF(RET_VALUE)
  MESSAGE(FATAL_ERROR "Could not detect the location of site-package in the build directory")
ENDIF(RET_VALUE)

STRING(REGEX REPLACE "(\r?\n)+$" "" PYTHON_LOCAL_SITE_PACKAGE "${PYTHON_LOCAL_SITE_PACKAGE}")
MESSAGE(STATUS "Python is installing its packages in ${PYTHON_LOCAL_SITE_PACKAGE}") 



IF(INTERNAL_CYTHON)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
           "-DPYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}"
           "-DPYTHON_LOCAL_SITE_PACKAGE=${PYTHON_LOCAL_SITE_PACKAGE}"
           "-DTARGET_PATH=${CMAKE_BINARY_DIR}/ext_build/python" "-P") 
  ExternalProject_Add(cython
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${CYTHON_URL}
    PREFIX ${BUILD_PREFIX}/cython-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
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
           "-DPYTHON_LOCAL_SITE_PACKAGE=${PYTHON_LOCAL_SITE_PACKAGE}"
           "-DTARGET_PATH=${CMAKE_BINARY_DIR}/ext_build/python" "-P") 

  ExternalProject_Add(netcdf4-python
    DEPENDS ${PREV_PYTHON_BUILD} netcdf
    URL ${NETCDF4_PYTHON_URL}
    PREFIX ${BUILD_PREFIX}/netcdf4-python-prefix
    CONFIGURE_COMMAND echo "No configure" 
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT}  ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  )
  SET(PREV_PYTHON_BUILD ${PREV_PYTHON_BUILD} netcdf4-python) 
ENDIF(INTERNAL_NETCDF4_PYTHON)

IF(INTERNAL_HEALPY)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
           "-DPYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}"
           "-DPYTHON_CPPFLAGS:STRING=${PYTHON_CPPFLAGS}"
           "-DCFITSIO_EXT_LIB=${CFITSIO_LIBRARY}"
           "-DCFITSIO_EXT_INC=${CFITSIO_INCLUDE_PATH}"
           "-DCFITSIO_EXT_PREFIX=${CFITSIO_PREFIX}"
           "-DNETCDF4_DIR=${NETCDF_BIN_DIR}"
           "-DPYTHON_LDFLAGS:STRING=${PYTHON_LDFLAGS}"
           "-DPYTHON_LOCAL_SITE_PACKAGE=${PYTHON_LOCAL_SITE_PACKAGE}"
           "-DTARGET_PATH=${CMAKE_BINARY_DIR}/ext_build/python" "-P")

  ExternalProject_Add(healpy
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${HEALPY_URL}
    PREFIX ${BUILD_PREFIX}/healpy-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  )
ENDIF(INTERNAL_HEALPY)

IF(INTERNAL_ARGPARSE)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
           "-DPYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}"
           "-DPYTHON_LOCAL_SITE_PACKAGE=${PYTHON_LOCAL_SITE_PACKAGE}"
           "-DTARGET_PATH=${CMAKE_BINARY_DIR}/ext_build/python" "-P")

  ExternalProject_Add(setuptools
    URL ${SETUPTOOLS_URL}
    PREFIX ${BUILD_PREFIX}/setuptools-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  )

  ExternalProject_Add(argparse
    DEPENDS setuptools
    URL ${ARGPARSE_URL}
    PREFIX ${BUILD_PREFIX}/argparse-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
   )
  SET(AUXILIARY_PYTHON_DEPEND ${AUXILIARY_PYTHON_DEPEND} argparse)
ENDIF(INTERNAL_ARGPARSE)