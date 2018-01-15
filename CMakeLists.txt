cmake_minimum_required(VERSION 3.8.2)

project(keygen VERSION 0.5.0)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")


option(UNITTEST "Builds unit tests" ON)
message(STATUS "Building Unit Tests : ${UNITTEST}")

option(COVERAGE "Enables source code coverage" OFF)
message(STATUS "Test coverage : ${COVERAGE}")

option(SANITIZER_ASAN "Enable ASan" OFF)
message(STATUS "ASan : ${SANITIZER_ASAN}")

option(SANITIZER_UBSAN "Enable UBSan" OFF)
message(STATUS "UBSan : ${SANITIZER_UBSAN}")


option(DOXYFILE "Generates the Doxyfile for Doxygen documentation" OFF)
message(STATUS "Doxyfile : ${DOXYFILE}")


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(Sanitizer)

find_package(OpenSSL REQUIRED)
message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")


if( COVERAGE )
    include(Coverage)
endif()

include(Memcheck)
include(CompilerOptions)


include_directories("include")
add_subdirectory(src)


if( UNITTEST )
    enable_testing()
    add_subdirectory(test)
endif()

if( DOXYFILE )
    include(Doxygen)
endif()

