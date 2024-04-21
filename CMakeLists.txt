cmake_minimum_required(VERSION 3.14)

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

set(EXTERNAL_INSTALLATION_DIR ${CMAKE_BINARY_DIR}/thirdparty)

configure_file(config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp)
include_directories(${PROJECT_BINARY_BIN})

include(ExternalProject)

set(SRC_MAIN main.cpp)

add_subdirectory(utils)
add_subdirectory(core)
add_subdirectory(plugins)
add_subdirectory(wrapper)

if(YATE_UNIT_TEST)
    include(CTest)
    enable_testing()
    add_subdirectory(unittests)
endif()

if(YATE_STATIC_ANALYSIS)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK
                "--enable=all"
                "--inconclusive"
                "--force"
                "--inline-suppr"
                "--suppress=missingIncludeSystem"
                "--suppress=*:*${CMAKE_BINARY_DIR}/*"
                "--xml"
                "--output-file=static_analysis.xml"
        )
    endif()
    set(CMAKE_CXX_CPPCHECK_BACKUP "{CMAKE_CXX_CPPCHECK}")
endif()

add_executable(${EXECUTABLE_NAME} ${SRC_MAIN})

target_link_libraries(${EXECUTABLE_NAME} core utils plugins wrapper)
target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

