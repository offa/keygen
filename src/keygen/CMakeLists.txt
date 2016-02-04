
add_library(keygen-lib KeyGen.c
                    Options.c
                    Output.c
                    )
set_target_properties(keygen-lib PROPERTIES ARCHIVE_OUTPUT_NAME "keygen"
                                            ARCHIVE_OUTPUT_DIRECTORY "lib"
                                            )
target_link_libraries(keygen-lib ${OPENSSL_LIBRARIES})
