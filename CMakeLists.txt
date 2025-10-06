cmake_minimum_required(VERSION 3.10)
project(raylib_jet_cpp)

set(CMAKE_CXX_STANDARD 17)

# Collect all cpp files from src/
file(GLOB_RECURSE SRC_MAIN src/*.cpp)

# Create the executable
add_executable(raylib_jet_cpp
    ${SRC_MAIN}
    # ${SRC_CORE}
    # ${SRC_ENTITIES}
    # ${SRC_SYSTEMS}
    # ${SRC_UI}
)

# Tell CMake where to find *your* headers
target_include_directories(raylib_jet_cpp PRIVATE include)

# Tell CMake where to find raylib headers/libs
target_include_directories(raylib_jet_cpp PRIVATE external)
target_link_directories(raylib_jet_cpp PRIVATE lib)

# Link Raylib + Windows system libs
target_link_libraries(raylib_jet_cpp raylib opengl32 gdi32 winmm)
