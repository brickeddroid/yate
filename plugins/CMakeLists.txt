
add_library(plugins STATIC)
#target_compile_features(plugins PUBLIC cxx_std_20)

add_subdirectory(ui)
target_link_libraries(plugins
    PUBLIC
        "${CMAKE_BINARY_DIR}/thirdparty/httpserver/src/httpserver-build/libhttpserver.a"  # Hier den tatsächlichen Namen der Bibliothek angeben
)
#target_sources(plugins PRIVATE $<TARGET_OBJECTS:uiplugins>)
#target_link_libraries(plugins INTERFACE uiplugins)

add_subdirectory(document)
#target_sources(plugins PRIVATE $<TARGET_OBJECTS:docplugins>)
#target_link_libraries(plugins INTERFACE documentplugins)
