message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(Criterion REQUIRED)

set(TEST_ARGS "--no-early-exit")

macro(_add_test _name)
    add_executable(${_name} "${_name}.c")
    target_include_directories(${_name} PUBLIC ${Criterion_INCLUDE_DIRS})
    target_link_libraries(${_name} keygen-lib ${OPENSSL_LIBRARIES} ${Criterion_LIBRARIES})
    add_test(NAME ${_name} COMMAND ${_name} ${TEST_ARGS})
endmacro(_add_test)

_add_test(ArgumentTest)
_add_test(FormatTest)
_add_test(MemoryTest)
_add_test(DataTest)
_add_test(OptionsTest)

add_custom_target(unittest ArgumentTest ${TEST_ARGS}
                            COMMAND FormatTest ${TEST_ARGS}
                            COMMAND MemoryTest ${TEST_ARGS}
                            COMMAND DataTest ${TEST_ARGS}
                            COMMAND OptionsTest ${TEST_ARGS}
                            )

