
add_c_library(keygen-lib KeyGen.c)
set_target_properties(keygen-lib PROPERTIES 
                                    ARCHIVE_OUTPUT_NAME "keygen"
                                    ARCHIVE_OUTPUT_DIRECTORY "lib"
                                    )
target_link_libraries(keygen-lib PRIVATE OpenSSL::SSL)



install(TARGETS keygen-lib EXPORT keygen-config DESTINATION include)
install(EXPORT keygen-config DESTINATION share/keygen/cmake)

