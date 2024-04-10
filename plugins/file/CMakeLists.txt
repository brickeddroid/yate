#target_sources(plugins
#    PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/uiplugin.cpp
#)
#
#target_include_directories(plugins
#    PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}
#)

target_sources(plugins
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/localfileio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fileiofactory.cpp
)

target_include_directories(plugins
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
