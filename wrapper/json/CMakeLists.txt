cmake_policy(SET CMP0135 NEW)
include(FetchContent)

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    PREFIX ${EXTERNAL_INSTALLATION_DIR}
    SOURCE_DIR ${EXTERNAL_INSTALLATION_DIR}/json
    BINARY_DIR ${EXTERNAL_INSTALLATION_DIR}/json-build
)
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
        ${EXTERNAL_INSTALLATION_DIR}/json/single_include/nlohmann
)


