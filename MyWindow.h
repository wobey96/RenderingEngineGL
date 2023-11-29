#pragma once

#include <stdio.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class MyWindow
{
public:
	MyWindow() = default;
	explicit MyWindow(GLint windowWidth, GLint windowHeight); 

	int Initialise();

	GLfloat getBufferWidth(); 
	GLfloat getBufferHeight(); 

	bool getShouldClose();

	void swapBuffers(); 

	virtual ~MyWindow(); 

private:
	GLFWwindow* mainWindow{ nullptr }; 

	GLint width{ 800 };
	GLint height{ 600 };

	GLint bufferWidth{ 0 };
	GLint bufferHeight{ 0 };
};

