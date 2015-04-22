message(STATUS "Building Unit Tests ${UNITTEST}")

set(CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)
set(CTEST_COMMAND "ctest")
set(CTEST_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test_unit_bin")

set(TEST_DIR ${CTEST_SOURCE_DIRECTORY})


find_package(Criterion REQUIRED)

macro(_add_test _name)
    set(TEST_NAME "${TEST_PREF}${_name}")
    add_test(NAME ${_name} COMMAND ${TEST_NAME})
    add_executable(${TEST_NAME} ${TEST_DIR}/${_name}.c)
    target_include_directories(${TEST_NAME} PUBLIC ${Criterion_INCLUDE_DIRS})
    target_link_libraries(${TEST_NAME} ${LIB_NAME} ${OPENSSL_LIBRARIES} ${Criterion_LIBRARIES})
endmacro(_add_test)

_add_test(ArgumentTest)
_add_test(FormatTest)
_add_test(MemoryTest)
_add_test(DataTest)