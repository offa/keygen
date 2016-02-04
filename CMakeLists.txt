cmake_minimum_required(VERSION 2.8.11)

project(keygen)
set(PROJECT_VERSION 0.2.3)

option(UNITTEST "Builds unit tests" ON)
option(COVERAGE "Enables source code coverage" OFF)
option(DOXYFILE "Generates the Doxyfile for Doxygen documentation" ON)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories("include")


find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

if( OPENSSL_FOUND )
	include_directories(${OPENSSL_INCLUDE_DIRS})
	message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif()

if( UNITTEST )
    enable_testing()
    subdirs(test)
endif()

include(Coverage)
include(Doxygen)

add_definitions(-std=c99 -Wall -Wextra -Werror -pedantic)
add_definitions(-DKEYGEN_VERSION="${PROJECT_VERSION}")

subdirs(src)

