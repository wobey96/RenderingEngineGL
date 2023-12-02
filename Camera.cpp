#include "Camera.h"


Camera::Camera(glm::vec3& startPosition, glm::vec3& startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
	:position(startPosition), up(startUp), yaw(startYaw), pitch(startPitch), movementSpeed(startMoveSpeed), turnSpeed(startTurnSpeed)
{
}

Camera::~Camera()
{

}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); 
	front.y = sin(glm::radians(pitch));
	front = glm::normalize(front); 

	right = glm::normalize(glm::cross(front, worldUp)); 
	up = glm::normalize(glm::cross(right, front)); 
}

