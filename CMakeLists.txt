# Set minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Options
option(UNIT_TESTING "Enable unit tests" ON)
option(USE_MN5 "Optimize for MN5" OFF)
option(USE_GPU "Enable GPU support" ON)

# Folder with files configuring extra CMake options
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Force MPI compìlers
set(ENV{CXX} "mpicxx")

# Set project name, version and languages
if(USE_GPU)
    project(Eigen_KS LANGUAGES CXX CUDA)
else()
    project(Eigen_KS LANGUAGES CXX)
endif()

include(mpi)
include(gpu)
include(compilerOps)

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)

if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")

add_subdirectory(src)

if(UNIT_TESTING)
    enable_testing()
    add_subdirectory(Tests)
endif()