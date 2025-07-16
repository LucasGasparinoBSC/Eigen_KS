project(utils)

# Define project folders
set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/sources)
set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/includes)

# Find project files
file(GLOB_RECURSE SRC_FILES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE INC_FILES ${INCLUDES_DIR}/*.h)

# If GPU usage enabled, set the CUDA target folders and add the CUDA related files
if(USE_GPU)
    set(CUDA_SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/gpuSources)
    set(CUDA_INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/gpuIncludes)
    file(GLOB_RECURSE CUDA_SRC_FILES ${CUDA_SOURCES_DIR}/*.cu)
    file(GLOB_RECURSE CUDA_INC_FILES ${CUDA_INCLUDES_DIR}/*.cuh)
    # Append the new sources/includes to the existing lists
    list(APPEND SRC_FILES ${CUDA_SRC_FILES})
    list(APPEND INC_FILES ${CUDA_INC_FILES})
endif()

# Set the directories for headers
if(USE_GPU)
    include_directories(SYSTEM ${CUDA_INCLUDES_DIR} ${INCLUDES_DIR})
else()
    include_directories(SYSTEM ${INCLUDES_DIR})
endif(USE_GPU)


# Build the library
add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${SRC_FILES} ${INC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(USE_GPU)
    set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDES_DIR} ${CUDA_INCLUDES_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
else()
    set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDES_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
endif()


install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${INC_FILES} DESTINATION include)