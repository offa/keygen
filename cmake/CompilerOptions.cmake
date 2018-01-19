set(COMMON_FLAGS
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Wshadow
        )

set(C_FLAGS ${COMMON_FLAGS})
set(CPP_FLAGS ${COMMON_FLAGS}
        -Wold-style-cast
        )


function(add_c_library name)
    add_library(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${C_FLAGS})
endfunction()

function(add_c_executable name)
    add_executable(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${C_FLAGS})
endfunction()


function(add_cpp_library name)
    add_library(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${CPP_FLAGS})
endfunction()

function(add_cpp_executable name)
    add_executable(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${CPP_FLAGS})
endfunction()

