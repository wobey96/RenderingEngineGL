#define STB_IMAGE_IMPLEMENTATION

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
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;  

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = { // value 4 and 6 is for UV (coordiantes of textures bounded to each vertex 
	//	x		y	  z	    u     v				// remember u and v are texture coordinates 
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,  0.5f, 0.0f,
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,   0.5f, 1.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
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
	MyWindow *mainWindow = new MyWindow(800, 600);
	mainWindow->Initialise();

	CreateObjects();
	CreateShaders();

	Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f); 

	Texture brickTexture = Texture((char*)("Textures/brick.png"));
	brickTexture.loadTexture();

	Texture dirtTexture = Texture((char*)("Textures/dirt.png"));
	dirtTexture.loadTexture();

	Light mainLight = Light(1.0f, 1.0f, 1.0f, 0.4f); // shouldn't change much 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbidentColor = 0;	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), mainWindow->getBufferWidth() / mainWindow->getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow->getShouldClose())
	{

		GLfloat now = static_cast<GLfloat>(glfwGetTime()); // if using sdl its' SDL_GetPerformanceCounter(); or something like that idk 
		deltaTime = now - lastTime; // how much time has passed sicne the last loop 
									// if using sdl: (now - lastTime)*1000/SDL_GetPerformanceFrequencey()
		lastTime = now; 

		// Get + Handle User Input
		glfwPollEvents();

		//user input for camera 
		camera->keyControl(mainWindow->getKeys(), deltaTime);
		camera->mouseControl(mainWindow->getXChange(), mainWindow->getYChange()); 

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation(); 
		uniformAmbidentColor = shaderList[0]->GetAmbientColourLocation(); 
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation(); 

		// putting light into action 
		mainLight.UseLight(uniformAmbientIntensity, uniformAmbidentColor); 
		

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); // might put projection in camera later for zoom
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		brickTexture.useTexture(); 
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.useTexture(); 
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow->swapBuffers();
	}

	////////// ---------- FREE MEMORY ---------- //////////

	// free meshList memory 
	for (auto& i : meshList)
	{
		delete i; 
	}
	meshList.erase(meshList.begin(), meshList.end()); 

	// free shaderList memory
	for (auto& i : shaderList)
	{
		delete i;
	}
	shaderList.erase(shaderList.begin(), shaderList.end()); 

	// free mainWindow 
	delete mainWindow; 
	mainWindow = nullptr; 

	return 0;
}