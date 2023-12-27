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

	/**
	* @brief Load texture into memory with various presets
	*/
	void loadTexture(); 

	/**
	* @brief Use the texture that was loaded into GPU memory by making it active
	*/
	void useTexture(); 

	/**
	* @brief Delete the texture that was loaded into GPU memory
	*/
	void clearTexture(); 

private:
	GLuint textureID{ 0 };
	int width{ 0 }; 
	int height{ 0 };
	int bitDepth{ 0 }; 

	char* fileLocation;
};


#endif // TEXTURE_H

