add_library(blosc2_plugin_example MODULE urfilters.c)

link_directories(${Python_LIB} ${Python_LIB64})

# target_include_directories(blosc2_plugin_example PRIVATE ${BLOSC2_INCLUDE_DIR})
install(TARGETS blosc2_plugin_example LIBRARY DESTINATION blosc2_plugin_example)
