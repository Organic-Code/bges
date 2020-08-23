cmake_minimum_required(VERSION 3.13)
project(bges)

include(cmake/configure.cmake)

option(BGES_STATIC_BACKEND "Should BGES use a module (.dll/.so file) (OFF) or is the backend built against BGES (ON) ?")
option(BGES_STATIC "Should BGES be built as an object file archive (static linking, .a/.lib) (ON) or as a ")

cmake_policy(SET CMP0063 NEW)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

### BGES Library

file(GLOB_RECURSE bges_sources sources/*.cpp)

if (BGES_STATIC)
    add_library(bges STATIC ${bges_sources})
else()
    add_library(bges SHARED ${bges_sources})
endif()
bges_configure_target(bges)
target_include_directories(bges PRIVATE includes/ sources/)
set_target_properties(bges PROPERTIES CXX_VISIBILITY_PRESET hidden)

if (HAS_PARENT)
    set(BGES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/includes PARENT_SCOPE)
    set(BGES_LIBRARIES $<TARGET_FILE:bges> PARENT_SCOPE)
endif()

if (BGES_STATIC_BACKEND)
    target_compile_definitions(bges PRIVATE BGES_STATIC_BACKEND=1)
else()
    target_compile_definitions(bges PRIVATE BGES_STATIC_BACKEND=0)
endif()



### BGES Backends

file(GLOB_RECURSE bges_sfml_sources backends/sfml/*.c backends/sfml/*.c)

add_library(bges_sfml-backend ${bges_sfml_sources})
bges_configure_target(bges_sfml-backend)





set_target_properties(bges_sfml-backend PROPERTIES CXX_VISIBILITY_PRESET hidden)
### Tests

find_package(Catch2 NO_MODULE)
if (CATCH2_FOUND)
    include(Catch)
    file(GLOB_RECURSE bges_tests_sources tests/*.cpp)
    add_executable(bges_tests ${bges_tests_sources})
    bges_configure_target(bges_tests)
    target_include_directories(bges_tests PRIVATE includes/ sources/ tests/ )
    target_link_libraries(bges_tests Catch2::Catch2)
    catch_discover_tests(bges_tests)
else()
    message(WARNING "Catch2 not found, unit tests won't be compiled")
endif()
