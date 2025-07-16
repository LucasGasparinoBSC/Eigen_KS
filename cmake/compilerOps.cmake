message("-- Selecting compiler Ops...")

# Force all libs to be shared type
set(LIBRARY_TYPE SHARED)

# Set a default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set C/C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set compilation config for certain compilers
message(STATUS "CXX compiler: ${CMAKE_CXX_COMPILER_ID}")

# Define common CXX compiler flags
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# If GPU usage is enabled, set CUDA flags and options
if(USE_GPU)
    message("-- Compiling with GPU support")
    message(STATUS "CUDA compiler: ${CMAKE_CUDA_COMPILER_ID}")
    # Set the compute capability and CUDA version
    set_cc()
    set_cuda()
    # Set the CUDA architecture
    set(CMAKE_CUDA_ARCHITECTURES ${GPU_CC})
    # Set basic NVCC flags
    set(CMAKE_CUDA_FLAGS "-pg -lineinfo -std=c++${CMAKE_CXX_STANDARD} -res-usage")
    # Set NVCC debug flags
    set(CMAKE_CUDA_FLAGS_DEBUG "-g -G -O0 -err-no")
    # Set NVCC release flags
    set(CMAKE_CUDA_FLAGS_RELEASE "-O3")
endif()

# Define specific compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("-- GNU compiler detected")

    # Common GNNU+MPI flags
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-cpp")

    # Debug
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} "-Wall -Wextra -Wpedantic")

    # Release
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "-march=native")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel" OR CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
    message("-- Intel compiler detected")

    # Common Intel+MPI flags
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "")

    # Debug
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} "-debug all")

    # Release
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "-qmkl -ipo -qopt-report=3")
    if(USE_MN5)
        message("Optimizing for MN5")
        set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "-xSAPPHIRERAPIDS")
    else()
        set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "-mtune=native")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC" OR CMAKE_CXX_COMPILER_ID STREQUAL "PGI")
    message("-- NVHPC compiler detected")

    # Set GPU characteristics
    set_cc()
    set_cuda()

    # Common NVHPC+MPI flags
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-cpp -lstdc++ -acc -cuda -gpu=cc${GPU_CC},cuda${GPU_CUDA},lineinfo")

    # Debug
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} "-Minform=inform -C -Mchkstk -traceback -Ktrap=fp -Minfo=all")

    # Release
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "-fast -Minfo=accel")
else()
    message("this shit: " ${CMAKE_C_COMPILER_ID})
    message(FATAL_ERROR "Unknown compiler")
endif()

# Adjust stringg so ; is removed from the command
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
string(REPLACE ";" " " CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

if(USE_GPU)
    string(REPLACE ";" " " CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS}")
    string(REPLACE ";" " " CMAKE_CUDA_FLAGS_DEBUG "${CMAKE_CUDA_FLAGS_DEBUG}")
    string(REPLACE ";" " " CMAKE_CUDA_FLAGS_RELEASE "${CMAKE_CUDA_FLAGS_RELEASE}")
endif(USE_GPU)
