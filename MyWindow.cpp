#include "MyWindow.h"



MyWindow::MyWindow(GLint windowWidth, GLint windowHeight)
	:width(windowWidth), height(windowHeight)
{

}



int MyWindow::initialize()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// enable depth testing so we know which ones to draw ontop of others
	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	return 0;
}



GLfloat MyWindow::getBufferWidth()
{
	return (GLfloat)bufferWidth; 
}



GLfloat MyWindow::getBufferHeight()
{
	return (GLfloat)bufferHeight;
}



bool MyWindow::getShouldClose()
{
	return glfwWindowShouldClose(mainWindow);
}



void MyWindow::swapBuffers()
{
	glfwSwapBuffers(mainWindow);
}



MyWindow::~MyWindow()
{
	// RAII
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
