target_sources(core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fileio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ifileiofactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/iobject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/iuiplugin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/iwrapper.cpp
)
target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
