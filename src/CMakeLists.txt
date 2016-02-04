subdirs("keygen")

add_executable(keygen Main.c)
set_target_properties(keygen PROPERTIES RUNTIME_OUTPUT_NAME "keygen"
                                        RUNTIME_OUTPUT_DIRECTORY "exe"
                                        )
target_link_libraries(keygen keygen-lib)

