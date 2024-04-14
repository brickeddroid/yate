cmake_minimum_required(VERSION 3.11)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_dependencies(wrapper nlohmann_json::nlohmann_json)

target_sources(wrapper
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/jsonwrapper.cpp
)
target_include_directories(wrapper
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_BINARY_DIR}/_deps/json-src/single_include/nlohmann
)


