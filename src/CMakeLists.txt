
set(SOURCES urfilters.c)

add_library(plugin_example MODULE ${SOURCES})

#install(TARGETS plugin_example DESTINATION ${CMAKE_SOURCE_DIR}/plugin_example)
install(TARGETS plugin_example
        LIBRARY COMPONENT LIB
        #ARCHIVE COMPONENT DEV
        #RUNTIME COMPONENT LIB
        DESTINATION . COMPONENT DEV)
