find_package(Doxygen REQUIRED)

set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
set(DOXYGEN_PROJECT_NUMBER ${PROJECT_VERSION})
set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN YES)

doxygen_add_docs(doc
                "${PROJECT_SOURCE_DIR}/include"
                "${PROJECT_SOURCE_DIR}/src"
                COMMENT "Generate Documentation"
                )

