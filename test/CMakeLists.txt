enable_cpp_options()

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "catch")


find_package(CppUTest REQUIRED)

add_library(testmain TestMain.cpp)
target_link_libraries(testmain PUBLIC Catch)

target_include_directories(testmain SYSTEM PUBLIC
                            ${CppUTest_INCLUDE_DIR}
                            ${CppUTest_Ext_INCLUDE_DIR}
                            )
target_link_libraries(testmain INTERFACE ${CppUTest_LIBRARY}
                                        ${CppUTest_Ext_LIBRARY}
                                        )


function(add_test_suite name)
    add_test(${name} ${name})
    target_link_libraries(${name} PRIVATE testmain build-libs)
endfunction()


list(APPEND OpenSSL::SSL)

add_executable(ArgumentTest ArgumentTest.cpp)
target_link_libraries(ArgumentTest PRIVATE keygen-lib)
add_test_suite(ArgumentTest)

add_executable(FormatTest FormatTest.cpp)
target_link_libraries(FormatTest PRIVATE keygen-lib)
add_test_suite(FormatTest)

add_executable(MemoryTest MemoryTest.cpp)
target_link_libraries(MemoryTest PRIVATE keygen-lib)
add_test_suite(MemoryTest)

add_executable(DataTest DataTest.cpp)
target_link_libraries(DataTest PRIVATE keygen-lib)
add_test_suite(DataTest)

add_executable(OptionsTest OptionsTest.cpp)
target_link_libraries(OptionsTest PRIVATE keygen-lib keygen-options)
add_test_suite(OptionsTest)

add_executable(MockedTest MockedTest.cpp)
target_link_libraries(MockedTest PRIVATE keygen-lib)
add_test_suite(MockedTest)



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

