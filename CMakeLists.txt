cmake_minimum_required(VERSION 3.5)

project(Yate
  VERSION 0.1.0
  DESCRIPTION "Yet another text editor"
  HOMEPAGE_URL "https://github.com/brickeddroid/yate"
  LANGUAGES CXX
)

set (EXECUTABLE_NAME "yate")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

configure_file(config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp)
include_directories(${PROJECT_BINARY_BIN})

include(ExternalProject)

set(SRC_MAIN main.cpp)

add_subdirectory(utils)
add_subdirectory(core)
add_subdirectory(plugins)
add_subdirectory(wrapper)

if(YATE_PROJECT_BUILD_TESTING)
  enable_testing()
  add_subdirectory(unittests)
endif()

add_executable(${EXECUTABLE_NAME} ${SRC_MAIN})

target_link_libraries(${EXECUTABLE_NAME} core utils plugins wrapper)
target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

