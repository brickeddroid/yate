add_library(utils
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/observablesubject.cpp
)
target_compile_features(utils PUBLIC cxx_std_20)
target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src

)
