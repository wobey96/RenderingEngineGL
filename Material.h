#ifndef MATERIAL_H

#include <GL\glew.h>

class Material
{
public:
	Material() = default; 
	explicit Material(GLfloat sIntensity, GLfloat shine); 
	~Material(); 

private:
	GLfloat specularintensity{ 0 }; // how bright the light is
	GLfloat shininess{ 0 }; // how collected the light is - aka (the cool kids call) specular power 
};


#endif // MATERIAL_H


