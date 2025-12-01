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

# Tell CMake where to find raylib headers/libs
target_include_directories(raylib_jet_cpp PRIVATE external)
target_link_directories(raylib_jet_cpp PRIVATE lib)
target_precompile_headers(raylib_jet_cpp PRIVATE include/Common.h)

# Link Raylib + Windows system libs
target_link_libraries(raylib_jet_cpp raylib opengl32 gdi32 winmm)
