#include "Shader.h"

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode); 
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation); 
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str(); 
	const char* fragmentCode = fragmentString.c_str(); 

	CompileShader(vertexCode, fragmentCode);  
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content; 
	std::ifstream fileStream(fileLocation, std::ios::in); 

	if (!fileStream.is_open())
	{
		std::cout << "Failed to read " << fileLocation << "! File doesn't exist." << std::endl;
		return std::string(); 
	}

	std::string line = ""; 
	while (!fileStream.eof())
	{
		std::getline(fileStream, line); 
		content.append(line + "\n");  // so we have a near output
	}

	fileStream.close(); 
	return content; 
}

GLint Shader::GetProjectionLocation()
{
	return uniformProjection;
}

GLint Shader::GetModelLocation()
{
	return uniformModel; 
}

GLint Shader::GetViewLocation()
{
	return uniformView;
}

GLint Shader::GetAmbientIntensityLocation()
{
	return uniformAmbientIntensity;
}

GLint Shader::GetAmbientColourLocation()
{
	return uniformAmbientColour;
}

GLint Shader::GetDiffuseIntensityLocation()
{
	return uniformDiffuseIntensity;  
}

GLint Shader::GetDirectionLocation()
{
	return uniformDirection; 
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		std::cout << "Failed to create shader" << std::endl;
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: " << eLog << std::endl; 
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: " << eLog << std::endl;
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view"); 
	uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour"); 
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity"); 
	uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction"); 
	uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity"); 
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		std::cout << "Error compiling the : " << shaderType << " shader: " << eLog << std::endl;
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::UseShader()
{
	glUseProgram(shaderID); 
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);  // deleting program off the GPU
		shaderID = 0; 
	}

	uniformModel = 0; 
	uniformProjection = 0; 
}

Shader::~Shader()
{
	// RAII deleting program off the GPU
	ClearShader(); 
}
