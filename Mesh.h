#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>
#include <GL\glew.h>

/**
* @brief This class provides an interface/wrapper for working with data structures created on GPU
*/
class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	/**
	* @brief Generates and binds VAOs, VBOs, and IBOs on GPU
	*/
	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVerticies, unsigned int numOfIndicies);

	/**
	* @brief Renders Data structures we've setup on the GPU
	*/
	void RenderMesh(); 

	/**
	* @brief Removes Data structures we've setup the GPU
	*/
	void ClearMesh(); 

private:
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };  
	GLuint IBO{ 0 };
	GLsizei indexCount{ 0 };
};

#endif // MESH_H

