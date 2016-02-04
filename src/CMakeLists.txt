subdirs(lib)

add_executable(keygen Main.c)
target_link_libraries(keygen keygen-lib)

