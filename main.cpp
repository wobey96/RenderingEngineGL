
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600; 

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
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        glfwSwapBuffers(mainWindow); 
    }

    return 0;
}
