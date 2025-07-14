project(utils)

# Define project folders
set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/sources)
set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/includes)

# Find project files
file(GLOB_RECURSE SRC_FILES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE INC_FILES ${INCLUDES_DIR}/*.h)

# Set the directories for headers
include_directories(SYSTEM ${INCLUDES_DIR})

# Build the library
add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${SRC_FILES} ${INC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDES_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${INC_FILES} DESTINATION include)