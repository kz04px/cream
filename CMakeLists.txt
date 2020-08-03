cmake_minimum_required(VERSION 3.12)

# Project
project(Cream VERSION 1.0 LANGUAGES CXX)

# Find packages
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Base directory relative includes
include_directories(src)
include_directories(include)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add the shared library
add_library(
    cream
    SHARED
    src/cream/engine.cpp
    src/cream/input.cpp
    src/cream/layers/layer-manager.cpp
    src/cream/models/materials.cpp
    src/cream/models/mesh.cpp
    src/cream/programs/programs.cpp
    src/cream/renderer/renderer2d.cpp
    src/cream/rendering/instance.cpp
    src/cream/rendering/line.cpp
    src/cream/rendering/model.cpp
    src/cream/rendering/tmodel.cpp
    src/cream/shaders/shaders.cpp
    src/cream/texture.cpp
    src/cream/window/linux-window.cpp
)

# Add an example executable
add_executable(
    basic
    examples/basic/main.cpp
)

target_link_libraries(cream glfw)
target_link_libraries(cream GLEW)
target_link_libraries(cream OpenGL)

target_link_libraries(basic cream)
