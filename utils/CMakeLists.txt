add_library(utils
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp
)
target_compile_features(utils PUBLIC cxx_std_20)
#target_include_directories(utils PUBLIC include)
#target_sources(utils PRIVATE ./log.cpp)
