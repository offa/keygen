subdirs("keygen")

add_library(keygen-options OBJECT Options.c)
add_library(keygen-output OBJECT Output.c)
target_compile_definitions(keygen-output PRIVATE -DKEYGEN_VERSION="${PROJECT_VERSION}")

add_executable(keygen Main.c $<TARGET_OBJECTS:keygen-options> $<TARGET_OBJECTS:keygen-output>)
set_target_properties(keygen PROPERTIES RUNTIME_OUTPUT_NAME "keygen"
                                        RUNTIME_OUTPUT_DIRECTORY "bin"
                                        )
target_link_libraries(keygen keygen-lib)

