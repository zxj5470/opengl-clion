#include "../headers/project_reference.h"
using namespace std;
using namespace glm;

#define Float GLfloat

// Vertex shader
const GLchar* vertexShaderSrc = R"glsl(
    #version 150 core

    in vec2 pos;

    void main()
    {
        gl_Position = vec4(pos, 0.0, 1.0);
    }
)glsl";

// Geometry shader
const GLchar* geometryShaderSrc = R"glsl(
    #version 150 core

    layout(points) in;
    layout(triangle_strip, max_vertices = 5) out;

    void main()
    {
        gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
        EmitVertex();

        EndPrimitive();
    }
)glsl";

// Fragment shader
const GLchar* fragmentShaderSrc = R"glsl(
    #version 150 core

    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)glsl";

// Shader creation helper
GLuint createShader(GLenum type, const GLchar* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}
string fvckString;
const GLchar* readText(const char *path){
    std::string shaderCode;
    std::ifstream shaderStream(path, std::ios::in);
    if(shaderStream.is_open()){
        std::string line;
        cout<<line<<endl;
        while(getline(shaderStream, line))
            shaderCode += "\n" + line;
        shaderStream.close();
    }else{
        cout<<"cannot open";
        return nullptr;
    }
    fvckString.clear();
    fvckString+=shaderCode;
    return fvckString.c_str();
}
int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    GLFWwindow *window;

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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    GLuint vertexShader = createShader(GL_VERTEX_SHADER, readText("shader/shader_vertex.glsl"));
    GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, readText("shader/shader_geom.glsl"));
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, readText("shader/shader_fragment.glsl"));

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    GLfloat points[] = {
            -0.45f,  0.45f,
            0.45f,  0.45f,
            0.45f, -0.45f,
            -0.45f, -0.45f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    bool running = true;

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                    glfwWindowShouldClose(window) == 0) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Render frame
        glDrawArrays(GL_POINTS, 0, 4);
        // Use our shader
        glDisableVertexAttribArray(0);
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}