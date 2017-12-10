cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl
        include/sources/main.cpp
        include/headers/project_reference.h
        include/headers/LoadShader.hpp)

target_link_libraries(opengl libglfw.so.3 GLEW GL)

add_executable(geoshader
        include/sources/geoshader.cpp
        include/headers/project_reference.h
        include/headers/LoadShader.hpp)

target_link_libraries(geoshader libglfw.so.3 GLEW GL)