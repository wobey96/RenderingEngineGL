#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <stdio.h>
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

/**
* @brief This class provides an interface/wrapper for working with the GLFW window
*/
class MyWindow
{
public:
	MyWindow() = default;
	explicit MyWindow(GLint windowWidth, GLint windowHeight); 
	virtual ~MyWindow();

	/**
	* @brief Initializes this class by setting up a GLFW window, properties, core profile, forward compatability
	* creates the window, allowing modern extension features, enable depth testing, and sets up viewport size,
	*/
	int Initialise();

	/**
	* @brief Getter for window buffer width
	*/
	GLfloat getBufferWidth(); 

	/**
	* @brief Getter for window buffer height
	*/
	GLfloat getBufferHeight(); 

	/**
	* @brief Checks if we should close window based on results of polling input
	*/
	bool getShouldClose();

	/**
	* @brief Double buffering swap
	*/
	void swapBuffers(); 

private:
	GLFWwindow* mainWindow{ nullptr }; 

	GLint width{ 800 };
	GLint height{ 600 };

	GLint bufferWidth{ 0 };
	GLint bufferHeight{ 0 };
};

#endif // MY_WINDOW_H

