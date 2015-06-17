message(STATUS "Building Unit Tests ${UNITTEST}")

set(CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)
set(CTEST_COMMAND "ctest")
set(CTEST_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test_unit_bin")

set(TEST_DIR ${CTEST_SOURCE_DIRECTORY})
set(TEST_ARGS "--no-early-exit")

find_package(Criterion REQUIRED)

add_custom_target(unittest)
add_custom_target(unittest.verbose)
add_custom_target(build-tests DEPENDS unittest)

macro(_add_test _name)
    add_test(NAME ${_name} COMMAND ${_name} ${TEST_ARGS})
    list(APPEND TEST_SRC "${TEST_DIR}/${_name}.c")

    if( ${ARGC} GREATER 1 )
        list(APPEND TEST_SRC "${ARGV1}")
    endif()

    add_executable(${_name} ${TEST_SRC})
    target_include_directories(${_name} PUBLIC ${Criterion_INCLUDE_DIRS})
    target_link_libraries(${_name} ${LIB_NAME} ${OPENSSL_LIBRARIES} ${Criterion_LIBRARIES})
    unset(TEST_SRC)

    add_custom_command(TARGET unittest POST_BUILD COMMAND ${_name} ${TEST_ARGS})
    add_custom_command(TARGET unittest.verbose POST_BUILD COMMAND ${_name} ${TEST_ARGS} "--verbose")
endmacro(_add_test)

_add_test(ArgumentTest)
_add_test(FormatTest)
_add_test(MemoryTest)
_add_test(DataTest)
_add_test(OptionsTest "../src/KGOptions.c")
