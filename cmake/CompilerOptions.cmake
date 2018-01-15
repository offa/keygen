set(COMMON_OPTIONS
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Wshadow
        )

set(C_OPTIONS ${COMMON_OPTIONS})
set(CPP_OPTIONS ${COMMON_OPTIONS}
        -Wold-style-cast
        )


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


function(enable_c_options)
    add_compile_options(${C_OPTIONS})
endfunction()

function(enable_cpp_options)
    add_compile_options(${CPP_OPTIONS})
endfunction()
