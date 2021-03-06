INCLUDE(FindPythonInterp)

SET(INTERNAL_NETCDF4_PYTHON ON)
SET(INTERNAL_CYTHON ON)
SET(INTERNAL_HEALPY ON)
SET(INTERNAL_SETUPTOOLS ON)
SET(INTERNAL_SCIPY ON)
SET(INTERNAL_KDTREE_SCIPY ON)

IF (INTERNAL_SETUPTOOLS)
  execute_process(
     COMMAND ${PYTHON_EXECUTABLE} -c "import setuptools; print(setuptools.__version__);" 
   RESULT_VARIABLE RET_VALUE
   OUTPUT_VARIABLE SETUPTOOLS_VERSION
  )
  IF (SETUPTOOLS_VERSION VERSION_GREATER 0.7)
	  message(STATUS "Setuptools recent. Not building it.")
    SET(INTERNAL_SETUPTOOLS OFF)
  ENDIF() 
ENDIF()

IF (PYTHON_VERSION_STRING VERSION_LESS 2.7)
  MESSAGE(STATUS "Python version is less than 2.7, argparse is needed.")
  SET(INTERNAL_ARGPARSE ON)
ELSE (PYTHON_VERSION_STRING VERSION_LESS 2.7)
  MESSAGE(STATUS "Python version is greater than 2.7, argparse is already bundled.")
ENDIF (PYTHON_VERSION_STRING VERSION_LESS 2.7)

IF(INTERNAL_CYTHON)
  SET(CYTHON_URL "https://files.pythonhosted.org/packages/d2/12/8ef44cede251b93322e8503fd6e1b25a0249fa498bebec191a5a06adbe51/Cython-0.28.4.tar.gz" CACHE STRING "URL to download Cython from")
  mark_as_advanced(CYTHON_URL)
ENDIF(INTERNAL_CYTHON)

IF(INTERNAL_NETCDF4_PYTHON)
  SET(NETCDF4_PYTHON_URL "https://github.com/Unidata/netcdf4-python/archive/v1.1.9rel.tar.gz" CACHE STRING "URL to download NetCDF4-python from")
  mark_as_advanced(NETCDF4_PYTHON_URL)
ENDIF(INTERNAL_NETCDF4_PYTHON)

IF (INTERNAL_HEALPY)
  SET(HEALPY_URL "http://github.com/healpy/healpy/archive/1.4.1.tar.gz" CACHE STRING "URL to download Healpy from")
  mark_as_advanced(HEALPY_URL)
ENDIF(INTERNAL_HEALPY)

IF(INTERNAL_SETUPTOOLS)
  SET(SETUPTOOLS_URL "https://pypi.python.org/packages/source/s/setuptools/setuptools-0.6c11.tar.gz" CACHE STRING "URL to download setuptools from")
  mark_as_advanced(SETUPTOOLS_URL)
ENDIF(INTERNAL_SETUPTOOLS)

IF(INTERNAL_ARGPARSE)
  SET(ARGPARSE_URL "http://argparse.googlecode.com/files/argparse-1.2.1.tar.gz" CACHE STRING "URL to download argparse from")
  mark_as_advanced(ARGPARSE_URL) 
ENDIF(INTERNAL_ARGPARSE)

IF(INTERNAL_SCIPY)
  SET(SCIPY_URL "https://pypi.python.org/packages/2f/12/565c08132db50a0ba34a33e0901f3d1d4d72e3b432ea828e4d87be5a4991/scipy-0.13.3.tar.gz" CACHE STRING "URL to download scipy from")
  mark_as_advanced(SCIPY_URL)
ENDIF(INTERNAL_SCIPY)

IF(INTERNAL_KDTREE_SCIPY)
  SET(KDTREE_SCIPY_URL "https://github.com/patvarilly/periodic_kdtree/archive/ea2d9e8c9d.zip" CACHE STRING "URL to download kdtree from")
  mark_as_advanced(KDTREE_SCIPY_URL)
ENDIF(INTERNAL_KDTREE_SCIPY)


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

# Create that directory
file(MAKE_DIRECTORY ${PYTHON_LOCAL_SITE_PACKAGE})

SET(BASIC_PYTHON_ENV "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} "
                     "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
                     "-DPYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}"
                     "-DPYTHON_LOCAL_SITE_PACKAGE=${PYTHON_LOCAL_SITE_PACKAGE}"
                     "-DTARGET_PATH=${CMAKE_BINARY_DIR}/ext_build/python")


IF(INTERNAL_CYTHON)
  SET(cosmotool_DEPS ${cosmotool_DEPS} cython)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
          ${BASIC_PYTHON_ENV}
          "-P") 
  ExternalProject_Add(cython
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${CYTHON_URL}
    URL_HASH SHA256=76ac2b08d3d956d77b574bb43cbf1d37bd58b9d50c04ba281303e695854ebc46
    PREFIX ${BUILD_PREFIX}/cython-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  ) 
  SET(PREV_PYTHON_BUILD ${PREV_PYTHON_BUILD} cython)
  file(WRITE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cython-wrap 
       "#!/bin/sh\n${CMAKE_BINARY_DIR}/run_python.sh ${CMAKE_BINARY_DIR}/ext_build/python/bin/cython $@\n")
  file(COPY ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cython-wrap 
       DESTINATION ${CMAKE_BINARY_DIR}/ext_build/python/bin
       FILE_PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
  SET(CYTHON_OPTION -DCYTHON:FILEPATH=${CMAKE_BINARY_DIR}/ext_build/python/bin/cython-wrap)
ELSE()
  SET(CYTHON_OPTION )
ENDIF(INTERNAL_CYTHON)


IF(INTERNAL_NETCDF4_PYTHON)
  SET(PYTHON_CPPFLAGS -I${NETCDF_INCLUDE_PATH})
  SET(PYTHON_LDFLAGS -L${NETCDF_BIN_DIR}/lib)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
          ${BASIC_PYTHON_ENV}
           "-DPYTHON_CPPFLAGS:STRING=${PYTHON_CPPFLAGS}"
           "-DHDF5_DIR=${HDF5_BIN_DIR}"
           "-DNETCDF4_DIR=${NETCDF_BIN_DIR}"
           "-DPYTHON_LDFLAGS:STRING=${PYTHON_LDFLAGS}"
           "-P") 

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
          ${BASIC_PYTHON_ENV}
           "-DPYTHON_CPPFLAGS:STRING=${PYTHON_CPPFLAGS}"
           "-DCFITSIO_EXT_LIB=${CFITSIO_LIBRARY}"
           "-DCFITSIO_EXT_INC=${CFITSIO_INCLUDE_PATH}"
           "-DCFITSIO_EXT_PREFIX=${CFITSIO_PREFIX}"
           "-DNETCDF4_DIR=${NETCDF_BIN_DIR}"
           "-DPYTHON_LDFLAGS:STRING=${PYTHON_LDFLAGS}"
           "-DSUPPORT_ARCH_NATIVE=${SUPPORT_ARCH_NATIVE}"
           "-P")

  ExternalProject_Add(healpy
    DEPENDS cfitsio ${PREV_PYTHON_BUILD}
    URL ${HEALPY_URL}
    PREFIX ${BUILD_PREFIX}/healpy-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  )
ENDIF(INTERNAL_HEALPY)

IF(INTERNAL_SETUPTOOLS)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
          ${BASIC_PYTHON_ENV}
           "-P")

  ExternalProject_Add(setuptools
    URL ${SETUPTOOLS_URL}
    PREFIX ${BUILD_PREFIX}/setuptools-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
  )
  SET(PREV_PYTHON_BUILD ${PREV_PYTHON_BUILD} setuptools)
ENDIF(INTERNAL_SETUPTOOLS)

IF(INTERNAL_ARGPARSE)

  ExternalProject_Add(argparse
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${ARGPARSE_URL}
    PREFIX ${BUILD_PREFIX}/argparse-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
   )
  SET(AUXILIARY_PYTHON_DEPEND ${AUXILIARY_PYTHON_DEPEND} argparse)
ENDIF(INTERNAL_ARGPARSE)

IF(INTERNAL_SCIPY)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
          ${BASIC_PYTHON_ENV}
           "-P")

  ExternalProject_Add(scipy
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${SCIPY_URL}
    URL_HASH MD5=0547c1f8e8afad4009cc9b5ef17a2d4d
    PREFIX ${BUILD_PREFIX}/scipy-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
   )
   SET(PREV_PYTHON_BUILD ${PREV_PYTHON_BUILD} scipy)
ENDIF(INTERNAL_SCIPY)

IF(INTERNAL_KDTREE_SCIPY)
  SET(BUILD_ENVIRONMENT 
          ${CMAKE_COMMAND}
          ${BASIC_PYTHON_ENV}
           "-P")

  ExternalProject_Add(kdtree-scipy
    DEPENDS ${PREV_PYTHON_BUILD}
    URL ${KDTREE_SCIPY_URL}
    PREFIX ${BUILD_PREFIX}/kdtree-scipy-prefix
    CONFIGURE_COMMAND echo "No configure"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_build.cmake
    INSTALL_COMMAND ${BUILD_ENVIRONMENT} ${CMAKE_SOURCE_DIR}/external/python_install.cmake
    PATCH_COMMAND  ${CMAKE_COMMAND} 
      -DPATCH_FILE=${CMAKE_SOURCE_DIR}/external/patch_kdtree 
      -DBUILD_PREFIX=${BUILD_PREFIX}/kdtree-scipy-prefix 
      -DSOURCE_PREFIX=${BUILD_PREFIX}/kdtree-scipy-prefix/src/kdtree-scipy
      -P ${CMAKE_SOURCE_DIR}/external/check_and_apply_patch.cmake
   )

  SET(AUXILIARY_PYTHON_DEPEND ${AUXILIARY_PYTHON_DEPEND} kdtree-scipy)
ENDIF(INTERNAL_KDTREE_SCIPY)


