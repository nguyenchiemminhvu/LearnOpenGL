#ifndef __CAMERA_H__
#define __CAMERA_H__

#pragma once
#include "glfw\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

static GLdouble lastPosX = 0;
static GLdouble lastPosY = 0;

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 1.0f;
const GLfloat SENSITIVITIVE = 0.05f;
const GLfloat FIELD_OF_VIEW = 60.0f;

class Camera
{
public:

	enum CameraDirection
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,

		TOTAL_KEY
	};

	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat fieldOfView;
	GLfloat mouseSensitivitive;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void processKeyboard(CameraDirection direction, GLfloat deltaTime);
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, bool constrainPitch = true);
	void processMouseScroll(GLfloat yOffset);

private:
	void updateCameraVectors();
};

#endif //__CAMERA_H__