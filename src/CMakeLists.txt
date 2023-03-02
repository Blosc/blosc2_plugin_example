set(SOURCES urfilters.c)

add_library(plugin_example MODULE ${SOURCES})

install(TARGETS plugin_example DESTINATION plugin_example)
