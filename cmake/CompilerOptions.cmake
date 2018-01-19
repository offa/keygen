
macro(add_common_flags)
    set(flags_common ${flags_common} ${ARGN})
endmacro()

macro(add_c_flags)
    set(flags_c ${flags_c} ${ARGN})
endmacro()

macro(add_cpp_flags)
    set(flags_cpp ${flags_cpp} ${ARGN})
endmacro()


function(add_c_library name)
    add_library(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_common} ${flags_c})
endfunction()

function(add_c_executable name)
    add_executable(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_common} ${flags_c})
endfunction()


function(add_cpp_library name)
    add_library(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_common} ${flags_cpp})
endfunction()

function(add_cpp_executable name)
    add_executable(${name} ${ARGN})
    target_compile_options(${name} PRIVATE ${flags_common} ${flags_cpp})
endfunction()

