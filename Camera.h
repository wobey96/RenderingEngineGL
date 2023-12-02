#ifndef CAMERA_H
#define CAMERA_H

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera() = default; 
	explicit Camera(glm::vec3& startPosition, glm::vec3& startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, 
		GLfloat startTurnSpeed);
	virtual ~Camera();

private:
	glm::vec3 position{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 up{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 right{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 worldUp{ glm::vec3(0.0f, 0.0f, 0.0f) };// we need to know which way we're rotating in reference to/ up direction of world

	GLfloat yaw{ 0.0f }; // left to right
	GLfloat pitch{ 0.0f }; // up and down 
	//GLfloat roll{ 0.0f }; might use later for derieved camera class idk yet 

	GLfloat movementSpeed{ 0.0f }; // keyboard movement speed (wasd keys)
	GLfloat turnSpeed{ 0.0f }; // mouse movement speed (click and drag)

	void update();
};

#endif // CAMERA_H

