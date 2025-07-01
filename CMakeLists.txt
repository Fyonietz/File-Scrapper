CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(Sea)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE C_FILE "src/*.c")

add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
    ${C_FILE}
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC src
    PUBLIC header
)

# Platform-specific libraries
if(WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME}
        Comdlg32
        Ole32
    )
elseif(UNIX AND NOT APPLE)
    # Linux-specific libraries for tinyfiledialogs
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    
    target_link_libraries(${CMAKE_PROJECT_NAME}
        ${GTK3_LIBRARIES}
    )
    
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${GTK3_INCLUDE_DIRS}
    )
    
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        ${GTK3_CFLAGS_OTHER}
    )
endif()