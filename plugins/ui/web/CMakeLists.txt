cmake_minimum_required(VERSION 3.5)
include(ExternalProject)
find_package(Git REQUIRED)

set(EXTERNAL_INSTALLATION_DIR ${CMAKE_BINARY_DIR}/thirdparty/httpserver/src)

ExternalProject_Add(httpserver
    PREFIX ${EXTERNAL_INSTALLATION_DIR}
    GIT_REPOSITORY https://github.com/brickeddroid/small_httpserver.git
    GIT_TAG main
    TIMEOUT 10
    SOURCE_DIR ${EXTERNAL_INSTALLATION_DIR}/httpserver
    BINARY_DIR ${EXTERNAL_INSTALLATION_DIR}/httpserver-build
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND "" #${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" <SOURCE_DIR> # Keine Konfiguration notwendig, wenn das externe Projekt bereits ein CMake-Setup hat
    BUILD_COMMAND "" #${CMAKE_COMMAND} --build <BINARY_DIR>  # Hier ändern Sie den Build-Befehl entsprechend
    INSTALL_COMMAND "" # Keine Installation notwendig
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(httpserver BINARY_DIR)


# Hier fügen Sie die externe Bibliothek zu Ihrer Hauptbibliothek hinzu
#add_library(HttpServer STATIC IMPORTED)
#set_target_properties(HttpServer PROPERTIES
#    IMPORTED_LOCATION ${EXTERNAL_INSTALLATION_DIR}/httpserver-build/libhttpserver.a
#    INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_INSTALLATION_DIR}/httpserver/include
#)

#add_library(webui
#    OBJECT
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/webui.cpp
#)
target_sources(plugins
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/webui.cpp"
        "${EXTERNAL_INSTALLATION_DIR}/httpserver/src/httpserver.cpp"
        "${EXTERNAL_INSTALLATION_DIR}/httpserver/src/httpmessage.cpp"
)
#add_dependencies(plugins httpserver)

#find_library(HTTP_LIBRARY NAMES httpserver)
#target_link_libraries(webui PUBLIC ${HTTP_LIBRARY})
# Fügen Sie das Include-Verzeichnis der externen Bibliothek hinzu
target_include_directories(plugins
    PUBLIC
        "${EXTERNAL_INSTALLATION_DIR}/httpserver/include"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_directories(plugins
    PUBLIC
        ${BINARY_DIR}
)

get_target_property(MY_TARGET_SOURCES plugins INCLUDE_DIRECTORIES)
message(STATUS "Target sources of webui: ${MY_TARGET_SOURCES}")

get_target_property(MY_LINK_LIBS plugins LINK_LIBRARIES)
message(STATUS "Linked libs of webui: ${MY_LINK_LIBS}")

file(COPY ./frontend DESTINATION ${CMAKE_BINARY_DIR})
