
#include <iostream>
#include <string.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600; 

GLint VAO, VBO, shader; 

// Vertex Shader  
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout(location = 0) in vec3 pos;                                             \n\
                                                                              \n\
void main()                                                                   \n\ 
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, 0.4 * pos.z, 1.0);           \n\
}";   

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 color;                                                               \n\
                                                                              \n\
void main()                                                                   \n\ 
{                                                                             \n\
    color = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";                         

void CreateTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    }; 

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); 

    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);   
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    return; 
}


void compileShaders()
{
    shader = glCreateProgram(); 

    if (!shader)
    {
        printf("Error creating shader program! \n"); 
        return; 
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0; 
    GLchar eLog[1024] = { 0 }; 

    glLinkProgram(shader); 
}

int main()
{
    if (!glfwInit())
    {
        printf("GLFW init failed!"); 
        glfwTerminate(); 
        return 1; 
    }

    // setup GLFW window properties 
    //OpenGL Version  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile = no backwards copatability 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);

    if (!mainWindow)
    {
        printf("GLFW window creation failed");
        glfwTerminate(); 
        return 1; 
    }

    // Get Buffer Size Informtion 
    int bufferWidth = 0, bufferHeight = 0; 
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // set context for glew to use 
    glfwMakeContextCurrent(mainWindow); 

    // allow modern extension features 
    glewExperimental = GL_TRUE; 

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW init failed"); 
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
     
    // set viewport size 
    glViewport(0, 0, bufferWidth, bufferHeight); 

    // Loop until window closed     
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + handle user input events 
        glfwPollEvents(); 

        // clear Window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        glfwSwapBuffers(mainWindow); 
    }

    return 0;
}
