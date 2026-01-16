cmake_minimum_required(VERSION 3.10)
project(raylib_jet_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS OFF)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    set(RAYLIB_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(RAYLIB_BUILD_GAMES OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Collect all cpp files from src/
file(GLOB_RECURSE SRC_MAIN src/*.cpp)

# Create the executable
add_executable(raylib_jet_cpp
    ${SRC_MAIN}
)

# CMake headers
target_include_directories(raylib_jet_cpp PRIVATE
    include
    include/Core
    include/Entities
    include/Scenes
    include/System
    include/UI
)

# Copy assets from working directory
# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET raylib_jet_cpp
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/assets"
        "$<TARGET_FILE_DIR:raylib_jet_cpp>/assets"
    COMMENT "Copying assets to output directory"
)

# Tell CMake where to find raylib headers/libs
target_precompile_headers(raylib_jet_cpp PRIVATE include/Common.h)

# Link Raylib + Windows system libs
target_link_libraries(raylib_jet_cpp raylib)
