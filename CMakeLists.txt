cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 11)
#message("${GLM_INCLUDE_DIRS}")

add_executable(opengl main.cpp project_reference.h LoadShader.hpp)

target_link_libraries(opengl libglfw.so.3 GLEW GL)