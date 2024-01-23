#include "Light.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
	:colour(red, green, blue), ambientIntensity(aIntensity), direction(xDir, yDir, zDir), diffuseIntensity(dIntensity)
{

}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z); // our color values passed to shader with id: ambientColorLocation
	glUniform1f(ambientIntensityLocation, ambientIntensity); // our ambientIntensity values passed to shader id: ambientIntensityLocation

	glUniform3f(directionLocation, direction.x, direction.y, direction.z); 
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	
}
