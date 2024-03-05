cmake_minimum_required(VERSION 3.5)
# ^choose a CMake version to support (its own can of worms)
# see https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-1.html
project(Yate
  VERSION 0.0.1 # https://semver.org/spec/v0.1.0.html
  DESCRIPTION "Yet another text editor"
  HOMEPAGE_URL "https://github.com/brickeddroid/yate"
  LANGUAGES CXX
)
#cmake_policy(SET CMP0076 NEW)
set (EXECUTABLE_NAME "yate")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

configure_file(config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp)
include_directories(${PROJECT_BINARY_BIN})

#file(GLOB_RECURSE sources      main.cpp)

include(ExternalProject)

if(YATE_PROJECT_BUILD_TESTING)
  enable_testing()
  # or alternatively, `include(CTest)`, if you want to use CDash
  # https://cmake.org/cmake/help/book/mastering-cmake/chapter/CDash.html
endif()
#include_directories(src/plugins/)
#link_directories(src/plugins/)
#
set(SRC_MAIN main.cpp)
#add_subdirectory(thirdparty)

add_subdirectory(plugins)
add_subdirectory(wrapper)
add_subdirectory(core)
add_subdirectory(utils)

add_executable(${EXECUTABLE_NAME} ${SRC_MAIN})

target_link_libraries(${EXECUTABLE_NAME} core utils wrapper plugins)
target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

# ^I generally order these from lower to higher abstraction levels.
# Ex. if module1 uses module2, then add_subdirectory it _after_ module2.
# That allows doing target_link_libraries inside moduleN/CmakeLists.txt

