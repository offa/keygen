add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "catch")

add_library(Trompeloeil INTERFACE)
target_include_directories(Trompeloeil INTERFACE "trompeloeil")

add_cpp_library(testmain TestMain.cpp)
target_link_libraries(testmain PUBLIC Catch Trompeloeil)



function(add_test_suite name)
    add_cpp_executable(${name} ${ARGN})
    add_test(${name} ${name})
    target_link_libraries(${name} PRIVATE testmain build-libs)
endfunction()


add_test_suite(ArgumentTest ArgumentTest.cpp)
target_link_libraries(ArgumentTest PRIVATE keygen-lib)

add_test_suite(FormatTest FormatTest.cpp)
target_link_libraries(FormatTest PRIVATE keygen-lib)

add_test_suite(MemoryTest MemoryTest.cpp)
target_link_libraries(MemoryTest PRIVATE keygen-lib)

add_test_suite(DataTest DataTest.cpp)
target_link_libraries(DataTest PRIVATE keygen-lib)

add_test_suite(OptionsTest OptionsTest.cpp)
target_link_libraries(OptionsTest PRIVATE keygen-lib keygen-options)

add_test_suite(MockedTest MockedTest.cpp)
target_link_libraries(MockedTest PRIVATE keygen-lib)



add_custom_target(unittest ArgumentTest
                        COMMAND FormatTest
                        COMMAND MemoryTest
                        COMMAND DataTest
                        COMMAND OptionsTest
                        COMMAND MockedTest
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

