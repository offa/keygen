find_package(PkgConfig)
pkg_check_modules(PKG_CppUTest QUIET libCppUTest)
set(CppUTest_DEFINITIONS ${PKG_CppUTest_CFLAGS_OTHER})

find_path(CppUTest_INCLUDE_DIR "CppUTest/TestHarness.h"
                                HINTS ${PKG_CppUTest_INCLUDE_DIRS}
                                        "${CppUTest_DIR}/include"
                                )

find_library(CppUTest_LIBRARY NAMES CppUTest libCppUTest
                                HINTS ${PKG_CppUTest_LIBDIR}
                                        ${PKG_CppUTest_LIBRARY_DIRS}
                                        "${CppUTest_DIR}/lib"
                                )
find_library(CppUTestExt_LIBRARY NAMES CppUTestExt libCppUTestExt
                                HINTS ${PKG_CppUTest_LIBDIR}
                                        ${PKG_CppUTest_LIBRARY_DIRS}
                                        "${CppUTest_DIR}/lib"
                                )


set(CppUTest_LIBRARIES ${CppUTest_LIBRARY} ${CppUTestExt_LIBRARY})
set(CppUTest_INCLUDE_DIRS ${CppUTest_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppUTest DEFAULT_MSG
                                        CppUTest_LIBRARY
                                        CppUTestExt_LIBRARY
                                        CppUTest_INCLUDE_DIR
                                        )

mark_as_advanced(CppUTest_INCLUDE_DIR CppUTest_LIBRARY CppUTestExt_LIBRARY)

