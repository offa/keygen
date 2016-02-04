
add_library(keygen-lib KGKeyGen.c
                    KGOptions.c
                    KGOutput.c)
target_link_libraries(keygen-lib ${OPENSSL_LIBRARIES})
