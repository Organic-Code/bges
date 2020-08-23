
function(bges_configure_target target_name)
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        target_compile_definitions(${target_name} PRIVATE OS_WINDOWS NOMINMAX)

    elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        target_compile_definitions(${target_name} PRIVATE OS_LINUX)
    else()
        message(FATAL_ERROR "unsupported OS")
    endif()

    set_target_properties(
        ${target_name}
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            DEBUG_POSTFIX dbg
    )

    target_include_directories(${target_name} PRIVATE common/)
endfunction()

function(bges_link_threads target_name)
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        set(THREADS_PREFER_PTHREAD_FLAG ON)
        find_package(Threads REQUIRED)
        target_link_libraries(${target_name} Threads::Threads)
    endif()


endfunction()

function(bges_link_filesystem target_name)
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        target_link_libraries(${target_name} stdc++fs)
    endif()
endfunction()
