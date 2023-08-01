add_library(blosc2_plugin_example MODULE urfilters.c)

link_directories(${Python_LIB} ${Python_LIB64})

install(TARGETS blosc2_plugin_example LIBRARY DESTINATION blosc2_plugin_example)
