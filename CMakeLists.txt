cmake_minimum_required(VERSION 2.8.11)

project(keygen)
set(PROJECT_VERSION 0.0.5)

message(STATUS "~~ ${PROJECT_NAME} ${PROJECT_VERSION} ~~")

set(LIB_NAME lib${PROJECT_NAME})
set(APP_NAME ${PROJECT_NAME})

set(APP_HDR_PATH "include")
set(LIB_HDR_PATH "lib/include")

file(GLOB_RECURSE APP_SRC "src/*.c")
file(GLOB_RECURSE APP_HDR "${APP_HDR_PATH}/*.h")
file(GLOB_RECURSE LIB_SRC "lib/src/*.c")
file(GLOB_RECURSE LIB_HDR "${LIB_HDR_PATH}/*.c")

include_directories("lib/include")


find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

if( OPENSSL_FOUND )
	include_directories(${OPENSSL_INCLUDE_DIRS})
	message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif()

enable_testing()
subdirs(test)


add_definitions(-std=c99)
add_definitions(-Wall -Wextra -pedantic -Werror)
add_definitions(-DKEYGEN_VERSION="${PROJECT_VERSION}")


add_library(${LIB_NAME} ${LIB_SRC})
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")


add_executable(${APP_NAME} ${APP_SRC})
target_link_libraries(${APP_NAME} ${LIB_NAME} ${OPENSSL_LIBRARIES})
target_include_directories(${APP_NAME} PUBLIC ${APP_HDR_PATH})
