#include "Texture.h"


Texture::Texture(char* fileLoc)
	:fileLocation(fileLoc)
{

}

Texture::~Texture()
{
	//RAII
	clearTexture(); 
}

void Texture::loadTexture()
{
	// load in image from file location 
	unsigned char* textData = stbi_load(fileLocation, &width, &height, &bitDepth, 0); // basically done with stb lib
	if (!textData)
	{
		std::cout << "Failed to find the file" << std::endl; 
		return; 
	}

	glGenTextures(1, &textureID); 
	glBindTexture(GL_TEXTURE_2D, textureID); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap around x-axis and repeat pattern
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap around y-axis and repeat pattern
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // zoom out with linear filter (bluring)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // zoom in with linear filter (bluring)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData); 
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(textData); // freeing up data(texture) on CPU since our data(texture) is now on GPU
}

void Texture::useTexture()
{
	glActiveTexture(GL_TEXTURE0); // texture unit we want to access (make it active)
	glBindTexture(GL_TEXTURE_2D, textureID);   
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	height = 0; 
	width = 0; 
	bitDepth = 0; 
	fileLocation = nullptr; 
}







