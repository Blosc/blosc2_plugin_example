link_directories(${Python_LIB} ${Python_LIB64})

add_executable("test_plugin" "test_plugin.c")
target_link_libraries("test_plugin" blosc2)
