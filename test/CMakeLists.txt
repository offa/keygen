message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(CppUTest REQUIRED)

add_library(testmain OBJECT TestMain.cpp)
target_include_directories(testmain SYSTEM PUBLIC
                            ${CppUTest_INCLUDE_DIR}
                            ${CppUTest_Ext_INCLUDE_DIR}
                            )

macro(_add_test _NAME _SRC _LIBS)
    add_executable(${_NAME} ${_SRC} $<TARGET_OBJECTS:testmain>)
    add_test(NAME ${_NAME} COMMAND ${_NAME})

    target_include_directories(${_NAME} SYSTEM PUBLIC
                                ${CppUTest_INCLUDE_DIR}
                                ${CppUTest_Ext_INCLUDE_DIR}
                                )
    target_link_libraries(${_NAME} ${CppUTest_LIBRARY}
                                keygen-lib
                                ${${_LIBS}}
                                )
endmacro()


list(APPEND TEST_LIB ${OPENSSL_LIBRARIES})
list(APPEND MOCK_LIB ${CppUTest_Ext_LIBRARY})

_add_test(ArgumentTest ArgumentTest.cpp TEST_LIB)
_add_test(FormatTest FormatTest.cpp TEST_LIB)
_add_test(MemoryTest MemoryTest.cpp TEST_LIB)
_add_test(DataTest DataTest.cpp TEST_LIB)
_add_test(OptionsTest OptionsTest.cpp TEST_LIB)
_add_test(MockedTest MockedTest.cpp MOCK_LIB)

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

