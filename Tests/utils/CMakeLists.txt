project(utils_tests)

# Define project folders
set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR})

# Find project files
file(GLOB_RECURSE SRC_FILES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE INC_FILES ${INCLUDES_DIR}/*.h)

# If GPU usage enabled, set the CUDA target folders and add the CUDA related files
if(USE_GPU)
    set(CUDA_SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/gpuSources)
    set(CUDA_INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/gpuIncludes)
    file(GLOB_RECURSE CUDA_SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/*.cu)
    file(GLOB_RECURSE CUDA_INC_FILES ${CMAKE_CURRENT_LIST_DIR}/*.cuh)
    # Append the new sources/includes to the existing lists
    list(APPEND SRC_FILES ${CUDA_SRC_FILES})
    list(APPEND INC_FILES ${CUDA_INC_FILES})
endif()

# Set the directories for headers
include_directories(SYSTEM ${INCLUDES_DIR} ${utils_INCLUDE_DIRS})

# For each CPP source file, create a corresponding test executable
foreach(src_file ${SRC_FILES})
    message(STATUS "Adding test for source file: ${src_file}")
    get_filename_component(test_name ${src_file} NAME_WE)
    add_executable(${test_name} ${src_file} ${INC_FILES})
    target_link_libraries(${test_name} utils)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()