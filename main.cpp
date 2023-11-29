#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "MyWindow.h"
#include "Mesh.h"
#include "Shader.h"


std::vector<Mesh*> meshList; 
std::vector<Shader*> shaderList; 


// Vertex Shader file
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader file
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indicies[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indicies, 12, 12); 
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indicies, 12, 12);
	meshList.push_back(obj2);
}


void CreateShaders()
{
	Shader* shader1 = new Shader(); 
	shader1->createFromFiles(vShader, fShader); 
	shaderList.push_back(shader1);
}

int main()
{
	MyWindow* mainWindow = new MyWindow(800, 600);
	mainWindow->initialize(); 

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0; 
	glm::mat4 projection = glm::perspective(45.0f, mainWindow->getBufferWidth() / mainWindow->getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow->getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader(); // start of use program
		uniformModel = shaderList[0]->GetModelLocation(); 
		uniformProjection = shaderList[0]->GetProjectionLocation(); 

		glm::mat4 model = glm::mat4(1.0f);

		// frist object rendered and stuff
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f)); // scale by how fast program is executing 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); 

		// second object rendered and stuff 
		model = glm::mat4(1.0f); // Identity matrix so we clear out all the trnasformations 
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f)); // scale by how fast program is executing 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0); // end of use program

		mainWindow->swapBuffers();
	}

	return 0;
}