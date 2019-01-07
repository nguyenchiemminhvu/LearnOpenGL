#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
	: cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivitive(SENSITIVITIVE), fieldOfView(FIELD_OF_VIEW)
{
	this->cameraPosition = position;
	this->cameraUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

glm::mat4 Camera::getProjectionMatrix()
{
	extern int g_width;
	extern int g_height;
	return glm::perspective(glm::radians(fieldOfView), (float)g_width / g_height, 0.1f, 100.0f);
}

void Camera::processKeyboard(CameraDirection direction, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime * 5.0f;
	switch (direction)
	{
	case Camera::FORWARD:
		cameraPosition += cameraFront * velocity;
		break;
	case Camera::BACKWARD:
		cameraPosition -= cameraFront * velocity;
		break;
	case Camera::LEFT:
		cameraPosition -= (glm::cross(cameraFront, cameraUp)) * velocity;
		break;
	case Camera::RIGHT:
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
		break;
	}
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, bool constrainPitch)
{
	xOffset *= mouseSensitivitive;
	yOffset *= mouseSensitivitive;

	this->pitch += yOffset;
	this->yaw += xOffset;

	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yOffset)
{
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}