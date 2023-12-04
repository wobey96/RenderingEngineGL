#include "Camera.h"


Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
	:position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch), movementSpeed(startMoveSpeed), turnSpeed(startTurnSpeed)
{
	update(); 
}

Camera::~Camera()
{

}

void Camera::keyControl(std::array<bool, 1024>& keys, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime; 

	if (keys[GLFW_KEY_W]) // forward
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S]) //backwards
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A]) // left
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D]) // right
	{
		position += right * velocity;
	}

	// we don't need to call update since we're not changeing yaw or pitch
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed; 

	yaw += xChange; 
	pitch += yChange; 

	if (pitch > 89.0f) // 89 because things get wird when we do past 90 (looking up)
	{
		pitch = 89.0f; // max out at 89.0f degrees 
	}

	if (pitch < -89.0f) // same thing as above but when looking down
	{
		pitch - 89.0f;
	}

	// now we update 
	update(); 
}



glm::mat4 Camera::calculateViewMatrix()
{
	// calculates a matrix that looks at something and applys all the correct rotations
	// and translations that's needed to look at something from a given position 
	// Note: If we wanted to follow another character, we could possibly use the position + front of that other character?? hmmm 
	return  glm::lookAt(position, position + front, up);
}


void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); 
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); 
	front = glm::normalize(front); 

	right = glm::normalize(glm::cross(front, worldUp)); 
	up = glm::normalize(glm::cross(right, front)); 
}

