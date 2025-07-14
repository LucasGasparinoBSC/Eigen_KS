project(utils_tests)

# Define project folders
set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR})

# Find project files
file(GLOB_RECURSE SRC_FILES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE INC_FILES ${INCLUDES_DIR}/*.h)

# Set the directories for headers
include_directories(SYSTEM ${INCLUDES_DIR} ${utils_INCLUDE_DIRS})

# For each CPP source file, create a corresponding test executable
foreach(src_file ${SRC_FILES})
    get_filename_component(test_name ${src_file} NAME_WE)
    add_executable(${test_name} ${src_file} ${INC_FILES})
    target_link_libraries(${test_name} utils)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()