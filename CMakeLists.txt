cmake_minimum_required(VERSION 3.10)

project(peppermint C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

file(GLOB_RECURSE PROJECT_HEADERS
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/*.h"
)

add_library(particle_lib OBJECT
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}  # IDE sees the headers
)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})


target_include_directories(particle_lib
  PUBLIC
    "${PROJECT_SOURCE_DIR}/include" # Corrected path
)


# Main executable
add_executable(peppermint app/main.c) # Changed from src/main.c
target_link_libraries(peppermint PUBLIC particle_lib)
