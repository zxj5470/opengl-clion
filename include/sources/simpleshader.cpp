#include <project_reference.h>
#include <project_preparation.h>

using namespace std;
using namespace glm;

int main() {
    if(!initGL())return -1;

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // Variables:
    GLuint vbo;
    glGenBuffers(1, &vbo);

    float points[] = {
            -0.45f, 0.45f,
            0.45f, 0.45f,
            0.45f, -0.45f,
            -0.45f, -0.45f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


    // Compile Shader then Link and Use
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, readText("../shader/simple_vertex.glsl"));
    GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, readText("../shader/simple_geom.glsl"));
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, readText("../shader/simple_fragment.glsl"));

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    //link and use
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    //----------------



    // Specify layout of point data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    //TODO: 循环体里面写循环渲染的代码
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0) {
        // Clear the screen
        //TODO: 循环渲染的
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Render frame
        glDrawArrays(GL_POINTS, 0, 4);
        // Use our shader
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //TODO: 收尾工作
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}