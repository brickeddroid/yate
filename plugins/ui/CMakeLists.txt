target_sources(plugins
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/uiplugin.cpp
)

target_include_directories(plugins
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(web)
