#ifndef CAMERA_H
#define CAMERA_H

#include <array>

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>



class Camera
{
public:
	Camera() = default; 
	explicit Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, 
		GLfloat startTurnSpeed);
	~Camera();

	/**
	* @brief Gets user input from keybaord and calculates the direction based front vector * velocity fromwasd keys 
	*/
	void keyControl(std::array<bool, 1024>& keys, GLfloat deltaTime);

	/**
	* @brief Gets user input from mouse movement and calculates the direction based on x,y position, turn speed, and pitch
	*/
	void mouseControl(GLfloat xChange, GLfloat yChange);

	/**
	* @brief Calculates the view matrix using glm lookAt() function 
	*/
	glm::mat4 calculateViewMatrix(); 

	glm::vec3 getCameraPosition(); 

private:
	glm::vec3 position{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 worldUp{ glm::vec3(0.0f, 0.0f, 0.0f) };// we need to know which way we're rotating in reference to/ up direction of world
	glm::vec3 front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 up{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 right{ glm::vec3(0.0f, 0.0f, 0.0f) };

	GLfloat yaw{ 0.0f }; // left to right
	GLfloat pitch{ 0.0f }; // up and down 
	//GLfloat roll{ 0.0f }; might use later for derieved camera class idk yet 

	GLfloat movementSpeed{ 0.0f }; // keyboard movement speed (wasd keys)
	GLfloat turnSpeed{ 0.0f }; // mouse movement speed (click and drag)

	/**
	* @brief Calculates camera position (front, right, and up components) 
	*/
	void update();
};

#endif // CAMERA_H

