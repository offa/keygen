
message(STATUS "Code coverage ${COVERAGE}")

if( ${COVERAGE} )
    find_program(GCOV_EXEC gcov)

    if( NOT GCOV_EXEC )
        message(FATAL_ERROR "Executable for gcov not found!")
    endif()

    set(GCOV_FLAGS "-ftest-coverage -fprofile-arcs")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${GCOV_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${GCOV_FLAGS}")
    set(GCOV_SCRIPT "${CMAKE_BINARY_DIR}/GenerateCoverage.cmake")

    configure_file("${CMAKE_MODULE_PATH}/GenerateCoverage.cmake.in" ${GCOV_SCRIPT} @ONLY)
    add_custom_target(coverage "${CMAKE_COMMAND}" "-P" ${GCOV_SCRIPT})
endif()