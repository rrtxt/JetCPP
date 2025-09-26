cmake_minimum_required(VERSION 3.10)
project(raylib_pong_cpp)

set(CMAKE_CXX_STANDARD 17)

# Tell CMake where to find Raylib headers and libs
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(raylib_pong_cpp src/main.cpp)

# Link Raylib + Windows system libs
target_link_libraries(raylib_pong_cpp raylib opengl32 gdi32 winmm)
