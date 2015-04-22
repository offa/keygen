
find_package(PkgConfig)
pkg_check_modules(PKG_Criterion QUIET libcriterion)
set(Criterion_DEFINITIONS ${PKG_Criterion_CFLAGS_OTHER})

find_path(Criterion_INCLUDE_DIR "criterion/criterion.h" HINTS ${PKG_Criterion_INCLUDE_DIRS} PATH_SUFFIXES libcriterion)
find_library(Criterion_LIBRARY NAMES criterion libcriterion HINTS ${PKG_Criterion_LIBDIR} ${PKG_Criterion_LIBRARY_DIRS})

set(Criterion_LIBRARIES ${Criterion_LIBRARY})
set(Criterion_INCLUDE_DIRS ${Criterion_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Criterion DEFAULT_MSG Criterion_LIBRARY Criterion_INCLUDE_DIR)

mark_as_advanced(Criterion_INCLUDE_DIR Criterion_LIBRARY)