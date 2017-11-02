cmake_minimum_required(VERSION 3.8.2)

project(keygen VERSION 0.3.4)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")


option(UNITTEST "Builds unit tests" ON)
option(UNITTEST_VERBOSE "Verbose unit test output" OFF)
message(STATUS "Building Unit Tests : ${UNITTEST}")

option(COVERAGE "Enables source code coverage" OFF)
message(STATUS "Test coverage : ${COVERAGE}")

option(DOXYFILE "Generates the Doxyfile for Doxygen documentation" ON)
message(STATUS "Doxyfile : ${DOXYFILE}")


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


find_package(OpenSSL REQUIRED)
message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")

if( COVERAGE )
    include(Coverage)
endif()

include(Memcheck)

add_compile_options(-Wall
                    -Wextra
                    -Werror
                    -pedantic
                    -Wshadow
                    )

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories("include")
add_subdirectory(src)


if( UNITTEST )
    enable_testing()
    add_subdirectory(test)
endif()

if( DOXYFILE )
    include(Doxygen)
endif()

