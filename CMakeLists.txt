cmake_minimum_required(VERSION 3.10)
project(raylib_jet_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
target_include_directories(raylib_jet_cpp PRIVATE external)
target_link_directories(raylib_jet_cpp PRIVATE lib)
target_precompile_headers(raylib_jet_cpp PRIVATE include/Common.h)

# Link Raylib + Windows system libs
target_link_libraries(raylib_jet_cpp raylib opengl32 gdi32 winmm)
