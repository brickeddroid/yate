add_library(plugins STATIC)

target_link_libraries(plugins PRIVATE core)

add_subdirectory(file)
add_subdirectory(ui)

#add_subdirectory(document)
