message(STATUS "Building Unit Tests ${UNITTEST}")

set(CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)
set(CTEST_COMMAND "ctest")
set(CTEST_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CTEST_BINARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test_unit_bin")

set(TEST_DIR ${CTEST_SOURCE_DIRECTORY})

if( COVERAGE )
    set(TEST_ARGS "--no-early-exit")
endif()

find_package(Criterion REQUIRED)

macro(_add_test _name)
    add_test(NAME ${_name} COMMAND ${_name} ${TEST_ARGS})
    add_executable(${_name} ${TEST_DIR}/${_name}.c)
    target_include_directories(${_name} PUBLIC ${Criterion_INCLUDE_DIRS})
    target_link_libraries(${_name} ${LIB_NAME} ${OPENSSL_LIBRARIES} ${Criterion_LIBRARIES})
endmacro(_add_test)

_add_test(ArgumentTest)
_add_test(FormatTest)
_add_test(MemoryTest)
_add_test(DataTest)