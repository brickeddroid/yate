cmake_minimum_required(VERSION 3.5)

include(ExternalProject)

ExternalProject_Add(
    json_external
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/json_external
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG master
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND "" # Keine Konfiguration notwendig, wenn das externe Projekt bereits ein CMake-Setup hat
    BUILD_COMMAND "" # Kein Build notwendig, da wir die externe Bibliothek nicht selbst kompilieren
    INSTALL_COMMAND "" # Keine Installation notwendig
    LOG_DOWNLOAD ON
)

# Hier fügen Sie die externe Bibliothek zu Ihrer Hauptbibliothek hinzu
#add_library(wrapper STATIC)
add_dependencies(wrapper json_external)

target_sources(wrapper
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/jsonwrapper.cpp
)
target_include_directories(wrapper
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_BINARY_DIR}/thirdparty/json_external/src/json_external/include
)

# Fügen Sie das Include-Verzeichnis der externen Bibliothek hinzu
#target_include_directories(wrapper )

