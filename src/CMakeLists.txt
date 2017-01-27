subdirs("keygen")

add_library(keygen-cl OBJECT Options.c Output.c)

add_executable(keygen Main.c $<TARGET_OBJECTS:keygen-cl>)
set_target_properties(keygen PROPERTIES RUNTIME_OUTPUT_NAME "keygen"
                                        RUNTIME_OUTPUT_DIRECTORY "bin"
                                        )
target_compile_definitions(keygen PRIVATE -DKEYGEN_VERSION="${PROJECT_VERSION}")
target_link_libraries(keygen keygen-lib)

