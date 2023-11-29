#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>	
#include <string>

#include <GL\glew.h>

/**
* @brief This class provides an interface/wrapper for working with shaders (vertex and fragment)
*/
class Shader
{
public:
	Shader() = default;

	/**
	* @brief Create shader from string on GPU by compiling with CompileShader()  
	*/
	void createFromString(const char* vertexCode, const char* fragmentCode); 

	/**
	* @brief Create files from string on GPU by reading in file then compiling with CompileShader()
	*/
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation); 

	/**
	* @brief Reads in contents of shader files (.vert or .frag) and formats
	*/
	std::string ReadFile(const char* fileLocation);  

	/**
	* @brief Gets location of projection matrix from .vert file
	*/
	GLint GetProjectionLocation(); 

	/**
	* @brief Gets location of model matrix from .vert file
	*/
	GLint GetModelLocation(); 

	/**
	* @brief Uses shader program that's on GPU that contains .vert and .frag shader programs
	*/
	void UseShader(); 

	/**
	* @brief Removes shader program that's on GPU
	*/
	void ClearShader();


	virtual ~Shader(); 

private:
	GLuint shaderID{ 0 };
	GLuint uniformProjection{ 0 };
	GLuint uniformModel{ 0 }; 

	/**
	* @brief Creates empty program on GPU, adds already created vertex and fragment shader to empty program,
	* links program that was created on GPU, and finally validates program that was created on GPU 
	*/
	void CompileShader(const char* vertexCode, const char* fragmentCode);

	/**
	* @brief Creates shader on GPU with appropriate type, gets length of shader the actual shader code from the file,
	* compiles newly made shader on GPU, and attaches this newly made shader to the program that is also on GPU
	*/
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

#endif // SHADER_H
