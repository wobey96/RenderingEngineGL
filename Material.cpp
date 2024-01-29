#include "Material.h"

Material::Material(GLfloat sIntensity, GLfloat shine)
	: specularintensity(sIntensity), shininess(shine)
{
}

Material::~Material()
{
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularintensity);
	glUniform1f(shininessLocation, shininess); 
}
	