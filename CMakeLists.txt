cmake_minimum_required(VERSION 3.16)
project(bges)

include(cmake/configure.cmake)

option(BGES_STATIC_BACKEND "Should BGES use a module (load .dll/.so file at runtime) (OFF) or is the backend built against BGES (ON) ?")
option(BGES_STATIC_BACKEND_BUILD "Should the backends included in this project be built as object file archives (.a/.lib) (ON) or as a shared library (.dll/.so) (OFF) ?")
option(BGES_STATIC_BUILD "Should BGES be built as an object file archive (static linking, .a/.lib) (ON) or as a shared library (.dll/.so) (OFF) ?")

if (BGES_STATIC_BACKEND AND NOT DEFINED BGES_BACKEND_LIBRARIES)
    message(ERROR BGES_STATIC_BACKEND was defined to ${BGES_STATIC_BACKEND}, but the backend to link was not specified (please define BGES_BACKEND_LIBRARIES))
endif()


cmake_policy(SET CMP0063 NEW)

get_directory_property(HAS_PARENT PARENT_DIRECTORY)

### BGES Library

file(GLOB_RECURSE bges_sources sources/*.cpp)

if (BGES_STATIC_BUILD)
    add_library(bges STATIC ${bges_sources})
else()
    add_library(bges SHARED ${bges_sources})
endif()
bges_configure_target(bges)
bges_link_filesystem(bges)
bges_link_dll_loading(bges)
target_include_directories(bges PRIVATE includes/ sources/)
set_target_properties(bges PROPERTIES CXX_VISIBILITY_PRESET hidden)

if (HAS_PARENT)
    set(BGES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/includes PARENT_SCOPE)
    set(BGES_LIBRARIES $<TARGET_FILE:bges> PARENT_SCOPE)
endif()

if (BGES_STATIC_BACKEND)
    target_compile_definitions(bges PRIVATE BGES_STATIC_BACKEND=1)
    target_link_libraries(bges ${BGES_BACKEND_LIBRARIES})
else()
    target_compile_definitions(bges PRIVATE BGES_STATIC_BACKEND=0)
endif()



### BGES Backends

add_subdirectory(external/SFML)
foreach(sfml_target IN ITEMS sfml-system sfml-network sfml-window sfml-graphics sfml-audio sfml-main)
    if(TARGET ${sfml_target})
        set_target_properties(${sfml_target} PROPERTIES FOLDER external/SFML)
        foreach(type IN ITEMS RUNTIME LIBRARY ARCHIVE)
            set_target_properties(${sfml_target} PROPERTIES ${type}_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
            foreach(mode IN ITEMS DEBUG RELWITHDEBINFO RELEASE)
                set_target_properties(${target} PROPERTIES ${type}_OUTPUT_DIRECTORY_${mode} ${CMAKE_BINARY_DIR})
            endforeach()
        endforeach()
    endif()
endforeach()

if(CONFIG_OS_WINDOWS)
    set(ARCH_FOLDER "x86")
    if(CONFIG_ARCH_64)
        set(ARCH_FOLDER "x64")
    endif()
    configure_file(external/SFML/extlibs/bin/${ARCH_FOLDER}/openal32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
endif()

file(GLOB_RECURSE bges_sfml_sources backends/sfml/*.c backends/sfml/*.cpp)

if (BGES_STATIC_BACKEND_BUILD)
    add_library(bges_sfml-backend STATIC ${bges_sfml_sources})
else ()
    add_library(bges_sfml-backend SHARED ${bges_sfml_sources})
endif()
bges_configure_target(bges_sfml-backend)
target_link_libraries(bges_sfml-backend sfml-system sfml-window sfml-graphics sfml-audio)

set_target_properties(bges_sfml-backend PROPERTIES CXX_VISIBILITY_PRESET hidden)

### Tests

include(external/Catch2/Catch.cmake)

file(GLOB_RECURSE bges_tests_sources tests/*.cpp)
add_executable(bges_tests EXCLUDE_FROM_ALL ${bges_tests_sources})
bges_configure_target(bges_tests)
target_include_directories(bges_tests PRIVATE includes/ external/Catch2/include)
target_link_libraries(bges_tests bges)
bges_link_threads(bges_tests)

include(CTest)
