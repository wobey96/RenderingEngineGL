#include "Light.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
	:colour(red, green, blue), ambientIntensity(aIntensity)
{

}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation)
{
	glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z); // our color values passed to shader with id: ambientColorLocation
	glUniform1f(ambientIntensityLocation, ambientIntensity); // our ambientIntensity values passed to shader id: ambientIntensityLocation
}
