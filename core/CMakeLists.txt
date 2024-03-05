#file(GLOB_RECURSE sources      **/*.cpp **/*.hpp)

add_library(core
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/documenthandler.cpp
)
target_compile_features(core PUBLIC cxx_std_20)
add_subdirectory(interfaces)
