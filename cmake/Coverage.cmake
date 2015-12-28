
message(STATUS "Code coverage ${COVERAGE}")

if( ${COVERAGE} )

    # Find Lcov tools
    find_program(LCOV lcov DOC "LCov")
    find_program(LCOV_GENHTML genhtml DOC "LCov GenHtml")

    if( NOT LCOV OR NOT LCOV_GENHTML )
        message(SEND_ERROR "LCov tools not found")
    endif()


    # Files and folders
    set(COV_DIR "${CMAKE_BINARY_DIR}/coverage")
    set(COV_FILE "${COV_DIR}/${PROJECT_NAME}.info")

    if( NOT EXISTS ${COV_DIR} )
        file(MAKE_DIRECTORY ${COV_DIR})
    endif()


    # Compiler flags
    set(COV_FLAGS "-ftest-coverage -fprofile-arcs")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${COV_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COV_FLAGS}")


    # Make targets
    add_custom_target(coverage-clean ${CMAKE_COMMAND} -E make_directory ${COV_DIR}
                                    COMMAND ${LCOV}
                                    --directory ${CMAKE_SOURCE_DIR}
                                    --zerocounters

                                    WORKING_DIRECTORY ${COV_DIR}
                                    COMMENT "Zerocounter coverage data"
                                    VERBATIM
                                    )

    add_custom_target(coverage ${CMAKE_COMMAND} -E make_directory ${COV_DIR}
                                    COMMAND ${LCOV}
                                    --capture
                                    --directory ${CMAKE_SOURCE_DIR}
                                    --output-file ${COV_FILE}
                                    --no-external

                                    COMMAND ${LCOV}
                                    --remove ${COV_FILE} "test/*"
                                    --output-file ${COV_FILE}

                                    COMMAND ${LCOV_GENHTML} --legend ${COV_FILE}

                                    WORKING_DIRECTORY ${COV_DIR}
                                    COMMENT "Generate coverage data"
                                    VERBATIM
                                    )

endif()

