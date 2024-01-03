#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light() = default;

	explicit Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity); // todo: change rgb to vec3 color

	~Light() = default; 

	/**
	* @brief pass our color and intensity values to shaders 
	*/
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);  

private:
	glm::vec3 colour{ 1.0f, 1.0f, 1.0f };
	GLfloat ambientIntensity{ 1.0f };
	 

};

#endif // LIGHT_H

