cmake_policy(SET CMP0135 NEW)
project(unit_testing)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
unset(CMAKE_CXX_CPPCHECK)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  PREFIX ${EXTERNAL_INSTALLATION_DIR}
  SOURCE_DIR ${EXTERNAL_INSTALLATION_DIR}/googletest
  BINARY_DIR ${EXTERNAL_INSTALLATION_DIR}/googletest-build
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
#FetchContent_MakeAvailable(googlemock)

add_subdirectory(utils)
add_subdirectory(core)

set(CMAKE_CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK_BACKUP}")
