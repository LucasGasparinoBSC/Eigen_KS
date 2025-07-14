message("-- Configuring MPI, if appropriate...")

if(USE_MPI)
    find_package(MPI)

    if(NOT MPI_CXX_FOUND)
        # do nothing
        message(FATAL_ERROR "MPI not found!")
    endif()
endif()

function(set_mpi)
    if(NOT TARGET MPI::MPI_CXX)
        add_library(MPI::MPI_CXX IMPORTED INTERFACE)
        set_property(TARGET MPI::MPI_CXX
            PROPERTY INTERFACE_COMPILE_OPTIONS ${MPI_CXX_COMPILE_FLAGS})
        set_property(TARGET MPI::MPI_CXX
            PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${MPI_CXX_INCLUDE_PATH}")
        set_property(TARGET MPI::MPI_CXX
            PROPERTY INTERFACE_LINK_LIBRARIES ${MPI_CXX_LINK_FLAGS} ${MPI_CXX_LIBRARIES})
    endif()
    target_link_libraries(${PROJECT_NAME} MPI::MPI_CXX)
endfunction()