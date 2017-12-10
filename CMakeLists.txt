cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl
        include/sources/main.cpp
        include/headers/project_reference.h
        include/headers/LoadShader.hpp)

add_executable(geoshader
        include/sources/geoshader.cpp
        include/headers/project_reference.h
        include/headers/LoadShader.hpp)

add_executable(simple_shader
        include/sources/simpleshader.cpp
        include/headers/project_reference.h
        include/headers/LoadShader.hpp)


IF (WIN32)
ELSEIF (APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(opengl glfw GLEW ${OPENGL_LIBRARY})
    target_link_libraries(geoshader glfw GLEW ${OPENGL_LIBRARY})
    target_link_libraries(simple_shader glfw GLEW ${OPENGL_LIBRARY})
ELSEIF (UNIX)
    target_link_libraries(opengl libglfw.so.3 GLEW GL)
    target_link_libraries(geoshader libglfw.so.3 GLEW GL)
ENDIF ()
