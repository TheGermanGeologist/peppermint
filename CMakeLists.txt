cmake_minimum_required(VERSION 3.10)

project(peppermint C CXX)

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

# Force GoogleTest to use the shared (DLL) C runtime library (/MD or /MDd)
# This ensures consistency with the rest of the project, which appears to use /MDd.
set(gtest_force_shared_crt ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0 # Using the specific tag
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(mint_tests
            tests/test_main.cpp
            tests/sorting_tests.cpp)
target_link_libraries(mint_tests PRIVATE particle_lib GTest::gtest_main) # Link against particle_lib

include(GoogleTest)
gtest_discover_tests(mint_tests)