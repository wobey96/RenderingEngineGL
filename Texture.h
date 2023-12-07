#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL\glew.h>

#include "stb_image.h"

class Texture
{
public:
	Texture() = default; 
	explicit Texture(char* fileLoc);
	virtual ~Texture(); 

	void loadTexture(); 
	void useTexture(); 
	void clearTexture(); 
private:
	GLuint textureID; 
	int width{ 0 }; 
	int height{ 0 };
	int bitDepth{ 0 }; 

	char* fileLocation{ "" };
};


#endif // TEXTURE_H

