set(COMMON_OPTIONS
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Wshadow
        )

set(C_OPTIONS )
set(CPP_OPTIONS
        -Wold-style-cast
        )


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


function(enable_c_options)
    add_compile_options(${C_OPTIONS})
endfunction()

function(enable_cpp_options)
    add_compile_options(${CPP_OPTIONS})
endfunction()
