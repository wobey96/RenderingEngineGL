#pragma once

#include <vector>
#include <iostream>
#include <GL\glew.h>

class Mesh
{
public:
	Mesh() = default;

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVerticies, unsigned int numOfIndicies);
	void RenderMesh(); 
	void ClearMesh(); 

	virtual ~Mesh();

private:
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };  
	GLuint IBO{ 0 };
	GLsizei indexCount{ 0 };
};

