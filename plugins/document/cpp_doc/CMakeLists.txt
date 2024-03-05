#add_library(docplugins
#    OBJECT
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp_doc.cpp
#)
target_sources(plugins
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp_doc.cpp
)
target_include_directories(plugins
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
