#file(GLOB_RECURSE sources      **/*.cpp **/*.hpp)

add_library(core
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/documenthandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/document.cpp
)

target_link_libraries(core PRIVATE utils)
target_compile_features(core PUBLIC cxx_std_20)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(api)
