message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(CppUTest REQUIRED)

add_library(testmain OBJECT TestMain.cpp)
target_include_directories(testmain PUBLIC
                            ${CppUTest_INCLUDE_DIR}
                            ${CppUTestExt_INCLUDE_DIR}
                            )

macro(_add_test _NAME _SRC _LIBS)
    add_executable(${_NAME} ${_SRC} $<TARGET_OBJECTS:testmain>)
    add_test(NAME ${_NAME} COMMAND ${_NAME})

    target_include_directories(${_NAME} PUBLIC
                                ${CppUTest_INCLUDE_DIR}
                                ${CppUTestExt_INCLUDE_DIR}
                                )
    target_link_libraries(${_NAME} ${CppUTest_LIBRARY}
                                ${CppUTestExt_LIBRARY}
                                keygen-lib
                                ${${_LIBS}}
                                )
endmacro()


list(APPEND TEST_LIB ${OPENSSL_LIBRARIES})

_add_test(ArgumentTest ArgumentTest.cpp TEST_LIB)
_add_test(FormatTest FormatTest.cpp TEST_LIB)
_add_test(MemoryTest MemoryTest.cpp TEST_LIB)
_add_test(DataTest DataTest.cpp TEST_LIB)
_add_test(OptionsTest OptionsTest.cpp TEST_LIB)


add_custom_target(unittest ArgumentTest -c
                        COMMAND FormatTest -c
                        COMMAND MemoryTest -c
                        COMMAND DataTest -c
                        COMMAND OptionsTest -c
                        COMMENT "Running unittests\n\n"
                        VERBATIM
                        )

