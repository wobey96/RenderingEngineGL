#include "MyWindow.h"

MyWindow::MyWindow(GLint windowWidth, GLint windowHeight)
	:width(windowWidth), height(windowHeight)
{

}

MyWindow::~MyWindow()
{
	// RAII
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

int MyWindow::Initialise()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW initialisation failed!" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
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
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Get Buffer Size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialisation failed!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// enable depth testing so we know which ones to draw ontop of others
	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	return EXIT_SUCCESS;
}

GLfloat MyWindow::getBufferWidth()
{
	return  static_cast<GLfloat>(bufferWidth);
}

GLfloat MyWindow::getBufferHeight()
{
	return static_cast<GLfloat>(bufferHeight);
}

bool MyWindow::getShouldClose()
{
	return glfwWindowShouldClose(mainWindow);
}

void MyWindow::swapBuffers()
{
	glfwSwapBuffers(mainWindow);
}