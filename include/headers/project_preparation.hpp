//
// Created by zh on 2017/12/11.
//
#pragma once
#ifndef OPENGL_PROJECT_PREPARE_H
#define OPENGL_PROJECT_PREPARE_H

#include <project_reference.hpp>
#define SUCCEED 0
using namespace std;
static GLFWwindow *window;
static string fvckString;

// Shader creation helper
static GLuint createShader(GLenum type, const GLchar *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}


static const GLchar *readText(const char *path) {
    std::string shaderCode;
    std::ifstream shaderStream(path, std::ios::in);
    if (shaderStream.is_open()) {
        std::string line;
        cout << line << endl;
        while (getline(shaderStream, line))
            shaderCode += "\n" + line;
        shaderStream.close();
    } else {
        cout << "cannot open";
        return nullptr;
    }
    fvckString.clear();
    fvckString += shaderCode;
    return fvckString.c_str();
}

static int initGL() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(800, 600, "标题", nullptr, nullptr);
    if (window == nullptr) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Initialize GLEW
    glewExperimental = static_cast<GLboolean>(true); // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Dark blue background
    return 0;
}

#endif //OPENGL_PROJECT_PREPARE_H
