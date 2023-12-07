#include "Texture.h"


Texture::Texture(char* fileLoc)
	:fileLocation(fileLoc)
{
}

Texture::~Texture()
{
}

void Texture::loadTexture()
{
	unsigned char* textData = stbi_load(fileLocation, &width, &height, &bitDepth, 0); 
	if (!textData)
	{
		std::cout << "Failed to find the file" << std::endl; 
		return; 
	}

	glGenTextures(1, &textureID); 
	glBindTexture(GL_TEXTURE_2D, textureID); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap around x-axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap around y-axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // zoom out
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT); // zoom in

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData); 
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); 

	stbi_image_free(textData); 
}

void Texture::useTexture()
{

}

void Texture::clearTexture()
{

}







