message(STATUS "Building Tests")


set(CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)
set(CTEST_COMMAND "ctest")
set(CTEST_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test_bin")

set(TEST_DIR ${CTEST_SOURCE_DIRECTORY})
set(TEST_PREF "test__")


macro(_add_test _name)
    set(TEST_NAME "${TEST_PREF}${_name}")
    add_test(NAME ${_name} COMMAND ${TEST_NAME})
    add_executable(${TEST_NAME} ${TEST_DIR}/${_name}.c)
    target_link_libraries(${TEST_NAME} ${LIB_NAME} ${OPENSSL_LIBRARIES}) 
endmacro(_add_test)


_add_test(TestMemory)
_add_test(TestFormat)
_add_test(TestArguments)
_add_test(TestMisc)
