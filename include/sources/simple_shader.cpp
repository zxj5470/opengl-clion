#include <project_reference.hpp>
#include <project_preparation.hpp>

#define FLOAT_SIZE sizeof(float)
#define SUCCEED 0

using namespace std;
using namespace glm;


int main() {
    if (initGL() != SUCCEED)return -1;
    // todo list as follow:

    // Variables:

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);

    float points[] = {
            //  Coordinates  Color             Sides
            -0.45f, 0.45f, 1.0f, 0.0f, 0.0f, 4.0f,
            0.45f, 0.45f, 0.0f, 1.0f, 0.0f, 8.0f,
            0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
            -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


    // todo: Compile Shader then Link and Use
    // the relative path is `../shader/xxxxx.glsl` on account of executable in `cmake-build-debug` directory
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

    // Specify layout of point data
    //个人理解为是将渲染关系进行绑定
    // Specify layout of point data
    /**
     * void glVertexAttribPointer(
     * GLuint index             -> the identity for obj in shader program
     * GLint size               ->
     * GLenum type              -> type:`GL_FLOAT`
     * GLboolean normalized     -> 指定当被访问时，固定点数据值是否应该被归一化（GL_TRUE）或者直接转换为固定点值（GL_FALSE）。
     * GLsizei stride           -> offset for a series: `6 * sizeof(float)`
     * const GLvoid * pointer   -> offset for this series: GL_ARRAY_BUFFER...null value you can use `nullptr`
     * );
     */
    GLsizei singleLength = 6 * FLOAT_SIZE;

    GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, singleLength, nullptr);// C++ 11 nullptr,or use 0 in earlier version.

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, singleLength, (void *) (2 * FLOAT_SIZE));

    GLint sidesAttrib = glGetAttribLocation(shaderProgram, "sides");
    glEnableVertexAttribArray(sidesAttrib);
    glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE, singleLength, (void *) (5 * FLOAT_SIZE));

    // TODO: 循环体里面写循环渲染的代码
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        // Clear the screen
        //TODO: 循环渲染
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Render frame
        glDrawArrays(GL_POINTS, 0, 4);
        // Use our shader
        // GLFW Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // TODO: 收尾工作
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    // GLFW
    glfwTerminate();
    return 0;
}