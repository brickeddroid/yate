#add_library(docplugins
#    OBJECT
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/documentfactory.cpp
#)

#target_compile_features(docplugins PUBLIC cxx_std_20)
target_sources(plugins
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/documentfactory.cpp
)

add_subdirectory(cpp_doc)


