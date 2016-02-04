message(STATUS "Building Unit Tests ${UNITTEST}")

find_package(Criterion REQUIRED)

macro(_add_test _name)
    add_executable(${_name} "${_name}.c")
    target_include_directories(${_name} PUBLIC ${Criterion_INCLUDE_DIRS})
    target_link_libraries(${_name} keygen-lib ${OPENSSL_LIBRARIES} ${Criterion_LIBRARIES})
    add_test(NAME ${_name} COMMAND ${_name} "--no-early-exit")
endmacro(_add_test)

_add_test(ArgumentTest)
_add_test(FormatTest)
_add_test(MemoryTest)
_add_test(DataTest)
_add_test(OptionsTest)

add_custom_target(unittest ArgumentTest
                            COMMAND FormatTest
                            COMMAND MemoryTest
                            COMMAND DataTest
                            COMMAND OptionsTest
                            )

