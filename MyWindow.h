#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <stdio.h>
#include <iostream>
#include <array>

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
	* @brief Public getter for xChange variable
	*/
	GLfloat getXChange();

	/**
	* @brief Public getter for yChange variable
	*/
	GLfloat getYChange();

	/**
	* @brief Checks if we should close window based on results of polling input
	*/
	bool getShouldClose();

	std::array<bool, 1024>& getKeys(); 

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

	std::array<bool, 1024> keys{}; // 1024 for range of ASCII characters  
 

	// last coordinate
	GLfloat lastX{ 0.0f };
	GLfloat lastY{ 0.0f };

	// current coordinate - last coordinates result
	GLfloat xChange{ 0.0f };
	GLfloat yChange{ 0.0f };

	// check if this is the very first mosue movement
	// if it's the very first movement, we don't want to do anything
	bool mouseFirstMoved{ true }; 

	/**
	* @brief passes how we handle keyboard and mouse function to glfw
	*/
	void createCallBacks(); 

	/**
	* @brief defines how we handle keyboard (if it's pressed, no pressed, and valid input)
	*/
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);

	/**
	* @brief defines how we handle mouse movement (if it's the first movement, change in x, and change in y positions
	*/
	static void handleMouse(GLFWwindow* window, double xPos, double yPos); // xPos and yPos: curr mouse position from application
};

#endif // MY_WINDOW_H

