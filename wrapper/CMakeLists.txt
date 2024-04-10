add_library(wrapper STATIC)

target_link_libraries(wrapper PRIVATE core)
target_link_libraries(wrapper PRIVATE plugins)

add_subdirectory(json)
