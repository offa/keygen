cmake_minimum_required(VERSION 3.11)

project(keygen VERSION 0.5.3)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")


option(UNITTEST "Builds unit tests" ON)
message(STATUS "Building Unit Tests : ${UNITTEST}")

option(COVERAGE "Enables source code coverage" OFF)
message(STATUS "Test coverage : ${COVERAGE}")

option(SANITIZER_ASAN "Enable ASan" OFF)
message(STATUS "ASan : ${SANITIZER_ASAN}")

option(SANITIZER_UBSAN "Enable UBSan" OFF)
message(STATUS "UBSan : ${SANITIZER_UBSAN}")


option(DOXYGEN "Generate Doxygen documentation" OFF)
message(STATUS "Doxygen : ${DOXYGEN}")


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


find_package(OpenSSL REQUIRED)
message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerOptions)
add_common_flags(-Wall
    -Wextra
    -Werror
    -pedantic
    -pedantic-errors
    -Wshadow
    -Wnull-dereference
    -Wconversion
    -Wsign-conversion
    )
add_cpp_flags(-Wold-style-cast
    -Wold-style-cast
    -Wnon-virtual-dtor
    -Woverloaded-virtual
    )


include(Sanitizer)
include(Memcheck)
include(ClangFormat)

if( COVERAGE )
    include(Coverage)
endif()


include_directories("include")
add_subdirectory(src)


if( UNITTEST )
    enable_testing()
    add_subdirectory(test)
endif()

if( DOXYGEN )
    include(Doxygen)
endif()
