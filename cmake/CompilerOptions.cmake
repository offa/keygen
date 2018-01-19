set(flags_common
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Wshadow
        )

set(flags_c ${flags_common})
set(flags_cpp ${flags_common}
        -Wold-style-cast
        )


function(add_c_library name)
    add_library(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_c})
endfunction()

function(add_c_executable name)
    add_executable(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_c})
endfunction()


function(add_cpp_library name)
    add_library(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_cpp})
endfunction()

function(add_cpp_executable name)
    add_executable(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_cpp})
endfunction()

