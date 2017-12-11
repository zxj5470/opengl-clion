cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/headers)

add_executable(opengl
        include/sources/main.cpp
        include/headers/project_reference.hpp
        include/headers/load_shader.hpp)

add_executable(geoshader
        include/sources/geo_shader.cpp
        include/headers/project_reference.hpp
        include/headers/load_shader.hpp)

add_executable(simple_shader
        include/sources/simple_shader.cpp
        include/headers/project_reference.hpp
        include/headers/load_shader.hpp)

if (WIN32)
    message("build in Windows")
elseif (APPLE)
    message("build in MacOS")
    find_package(OpenGL REQUIRED)
    set(PROJECT_MACOSX_LIBS glfw GLEW ${OPENGL_LIBRARY})
    target_link_libraries(opengl ${PROJECT_MACOSX_LIBS})
    target_link_libraries(geoshader ${PROJECT_MACOSX_LIBS})
    target_link_libraries(simple_shader ${PROJECT_MACOSX_LIBS})
elseif (UNIX) # GNU is Not Uinx
    message("build in Linux")
    target_link_libraries(opengl libglfw.so.3 GLEW GL)
    target_link_libraries(geoshader libglfw.so.3 GLEW GL)
    target_link_libraries(simple_shader libglfw.so.3 GLEW GL)
endif ()
