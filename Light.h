#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light() = default;

	explicit Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
				   GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity); // todo: change rgb to vec3 color

	~Light() = default; 

	/**
	* @brief pass our color and intensity values to shaders 
	*/
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);  

private:
	glm::vec3 colour{ 1.0f, 1.0f, 1.0f };
	GLfloat ambientIntensity{ 1.0f }; // ambient lighting doesn't really rely on direction 

	glm::vec3 direction{ 0.0f, -1.0f, 0.0f };
	GLfloat diffuseIntensity{ 0.0f };
	 

};

#endif // LIGHT_H

