message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(CppUTest REQUIRED)

add_library(testmain TestMain.cpp)
target_include_directories(testmain SYSTEM PUBLIC
                            ${CppUTest_INCLUDE_DIR}
                            ${CppUTest_Ext_INCLUDE_DIR}
                            )

function(add_test_suite name src libs)
    add_executable(${name} ${src})
    add_test(NAME ${name} COMMAND ${name})
    target_link_libraries(${name} testmain
                                keygen-lib
                                ${CppUTest_LIBRARY}
                                ${${libs}}
                                )
endfunction()


list(APPEND TEST_LIB ${OPENSSL_LIBRARIES})
list(APPEND MOCK_LIB ${CppUTest_Ext_LIBRARY})

add_test_suite(ArgumentTest ArgumentTest.cpp TEST_LIB)
add_test_suite(FormatTest FormatTest.cpp TEST_LIB)
add_test_suite(MemoryTest MemoryTest.cpp TEST_LIB)
add_test_suite(DataTest DataTest.cpp TEST_LIB)
add_test_suite(OptionsTest OptionsTest.cpp TEST_LIB)
target_link_libraries(OptionsTest keygen-options)
add_test_suite(MockedTest MockedTest.cpp MOCK_LIB)

set(TEST_FLAGS -c)

if( UNITTEST_VERBOSE )
    set(TEST_FLAGS ${TEST_FLAGS} -v)
endif()

add_custom_target(unittest ArgumentTest ${TEST_FLAGS}
                        COMMAND FormatTest ${TEST_FLAGS}
                        COMMAND MemoryTest ${TEST_FLAGS}
                        COMMAND DataTest ${TEST_FLAGS}
                        COMMAND OptionsTest ${TEST_FLAGS}
                        COMMAND MockedTest ${TEST_FLAGS}
                        COMMENT "Running unittests\n\n"
                        VERBATIM
                        )


if( VALGRIND )
    add_custom_target(memcheck-test ${VALGRIND} ${VALGRIND_MEMCHECK_FLAGS} $<TARGET_FILE:FormatTest> 1> /dev/null
                        COMMAND ${VALGRIND} ${VALGRIND_MEMCHECK_FLAGS} $<TARGET_FILE:MemoryTest> 1> /dev/null
                        COMMAND ${VALGRIND} ${VALGRIND_MEMCHECK_FLAGS} $<TARGET_FILE:DataTest> 1> /dev/null
                        COMMAND ${VALGRIND} ${VALGRIND_MEMCHECK_FLAGS} $<TARGET_FILE:OptionsTest> 1> /dev/null
                        COMMAND ${VALGRIND} ${VALGRIND_MEMCHECK_FLAGS} $<TARGET_FILE:MockedTest> 1> /dev/null
                        COMMENT "Memchecking executable\n\n"
                        VERBATIM
                        )
endif()

