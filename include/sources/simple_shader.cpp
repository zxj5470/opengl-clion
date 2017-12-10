#include <project_reference.hpp>
#include <project_preparation.hpp>

#define SUCCEED 0

using namespace std;
using namespace glm;


int main() {
    if (initGL() != SUCCEED)return -1;

    // todo list is as follow:
    // Variables:
    float points[] = {
            //  Coordinates  Color             Sides
            -0.45f, 0.45f, 1.0f, 0.0f, 0.0f, 4.0f,
            0.45f, 0.45f, 0.0f, 1.0f, 0.0f, 8.0f,
            0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
            -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // TODO: Compile Shader then Link and Use
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

    /* todo:
     * 个人理解为 将渲染关系进行绑定
     * void glVertexAttribPointer(
     * GLuint index             -> the identity for obj in shader program
     * GLint size               ->
     * GLenum type              -> type:`GL_FLOAT`
     * GLboolean normalized     -> 指定当被访问时，固定点数据值是否应该被归一化（GL_TRUE）或者直接转换为固定点值（GL_FALSE）。
     * GLsizei stride           -> offset for a series: `6 * sizeof(float)`
     * const GLvoid * pointer   -> offset for this series: GL_ARRAY_BUFFER...null value you can use `nullptr`
     * );
     */

#define var auto
#define FLOAT_SIZE sizeof(float)

    GLsizei singleLength = 6 * FLOAT_SIZE;
    var posAttr = (GLuint) glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttr);
    glVertexAttribPointer(posAttr, 2, GL_FLOAT, GL_FALSE, singleLength,
                          nullptr);// C++ 11 nullptr,or use 0 in earlier version.

    // col 会引起歧义。命名应尽量避免这样的命名。
    var colorAttr = (GLuint) glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttr);
    glVertexAttribPointer(colorAttr, 3, GL_FLOAT, GL_FALSE, singleLength, (void *) (2 * FLOAT_SIZE));

    var sidesAttr = (GLuint) glGetAttribLocation(shaderProgram, "sides");
    glEnableVertexAttribArray(sidesAttr);
    glVertexAttribPointer(sidesAttr, 1, GL_FLOAT, GL_FALSE, singleLength, (void *) (5 * FLOAT_SIZE));

#undef var
#undef FLOAT_SIZE

    // TODO: 循环体里面写循环渲染的代码
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        //TODO: 循环渲染
        // Clear the screen
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