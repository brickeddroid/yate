cmake_minimum_required(VERSION 3.14)

set(EXTERNAL_INSTALLATION_DIR ${CMAKE_BINARY_DIR}/thirdparty/httpserver/src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  httpserver
  PREFIX ${EXTERNAL_INSTALLATION_DIR}
  SOURCE_DIR ${EXTERNAL_INSTALLATION_DIR}/httpserver
  BINARY_DIR ${EXTERNAL_INSTALLATION_DIR}/httpserver-build
  GIT_REPOSITORY https://github.com/brickeddroid/small_httpserver.git
  GIT_TAG main
)
FetchContent_MakeAvailable(httpserver)

target_sources(plugins
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/webui.cpp"
        "${EXTERNAL_INSTALLATION_DIR}/httpserver/src/httpserver.cpp"
        "${EXTERNAL_INSTALLATION_DIR}/httpserver/src/httpmessage.cpp"
)

target_include_directories(plugins
    PUBLIC
        "${EXTERNAL_INSTALLATION_DIR}/httpserver/include"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_directories(plugins
    PUBLIC
        ${BINARY_DIR}
)

file(COPY ./frontend DESTINATION ${CMAKE_BINARY_DIR})
