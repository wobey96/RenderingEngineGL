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

	// Handle key + mouse input
	createCallBacks(); 
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // cursor not appearing on screen like in real games

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

	// make our window pointer for glfw know that we are talking about the window created with this class
	glfwSetWindowUserPointer(mainWindow, this); // make sure to review this again :/

	return EXIT_SUCCESS;
}

void MyWindow::createCallBacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys); 
	glfwSetCursorPosCallback(mainWindow, handleMouse);  
}

void MyWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window)); 

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE); 
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//std::cout << "Pressed " << key << std::endl;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//std::cout << "Released " << key << std::endl;
		}
	}
}

void MyWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

	// check if it's the very first movement 
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = static_cast<GLfloat>(xPos);
		theWindow->lastY = static_cast<GLfloat>(yPos); 
		theWindow->mouseFirstMoved = false; 
	}

	theWindow->xChange = static_cast<GLfloat>(xPos) - theWindow->lastX; 
	theWindow->yChange = theWindow->lastY - static_cast<GLfloat>(yPos); // Note: flipped around so we don't have inverted controls

	// updating so we're ready for the next input
	theWindow->lastX = static_cast<GLfloat>(xPos);
	theWindow->lastY = static_cast<GLfloat>(yPos);

	//std::cout << " x position: " << theWindow->xChange << " y position: " << theWindow->yChange << std::endl; 
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

std::array<bool, 1024>& MyWindow::getKeys()
{
	return keys;
}

void MyWindow::swapBuffers()
{
	glfwSwapBuffers(mainWindow);
}

GLfloat MyWindow::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange; 
}

GLfloat MyWindow::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}