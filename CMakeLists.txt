cmake_minimum_required(VERSION 2.8.11)

project(keygen)
set(PROJECT_VERSION 0.2.3)

option(UNITTEST "Builds unit tests" ON)
option(COVERAGE "Enables source code coverage" OFF)
option(DOXYFILE "Generates the Doxyfile for Doxygen documentation" ON)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(LIB_NAME lib${PROJECT_NAME})
set(APP_NAME ${PROJECT_NAME})

set(APP_HDR_PATH "include")
set(LIB_HDR_PATH "lib/include")

set(APP_SRC src/Main.c
            src/KGOutput.c
            src/KGOptions.c
    )
set(LIB_SRC lib/src/KGKeyGen.c)

include_directories(${LIB_HDR_PATH})
include_directories(${APP_HDR_PATH})


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

add_definitions(-std=c99)
add_definitions(-Wall -Wextra -pedantic -Werror)
add_definitions(-DKEYGEN_VERSION="${PROJECT_VERSION}")


add_library(${LIB_NAME} ${LIB_SRC})
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")


add_executable(${APP_NAME} ${APP_SRC})
target_link_libraries(${APP_NAME} ${LIB_NAME} ${OPENSSL_LIBRARIES})
