#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>	
#include <string>

#include <GL\glew.h>

class Shader
{
public:
	Shader() = default;

	void createFromString(const char* vertexCode, const char* fragmentCode); 
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation); 

	std::string ReadFile(const char* fileLocation);  

	GLint GetProjectionLocation(); 
	GLint GetModelLocation(); 

	void UseShader(); 
	void ClearShader();


	virtual ~Shader(); 

private:
	GLuint shaderID{ 0 };
	GLuint uniformProjection{ 0 };
	GLuint uniformModel{ 0 }; 

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

