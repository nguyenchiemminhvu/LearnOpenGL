#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Shader.h"
#include "Camera.h"

#include <iostream>

#define NUM_KEYS 512
bool pressed_keys[NUM_KEYS] = { false };

bool firstMouseEvent = true;
int lastMouseX, lastMouseY;

int g_width, g_height;

Camera *camera = new Camera();

void handleKeyPressed(GLFWwindow *window, int key)
{

}

void handleKeyReleased(GLFWwindow *window, int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void handleInput(GLFWwindow *window)
{
	for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS)
		{
			// handle key pressed
			// ------------------
			if (!pressed_keys[i])
			{
				pressed_keys[i] = true;
				handleKeyPressed(window, i);
			}
		}
		else
		{
			// handle key released
			// -------------------
			if (pressed_keys[i])
			{
				pressed_keys[i] = false;
				handleKeyReleased(window, i);
			}
		}
	}
}

void resizeCallback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window's dimensions
	// ----------------------------------------------------------
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *window, double posX, double posY)
{
	if (firstMouseEvent)
	{
		lastMouseX = posX;
		lastMouseY = posY;
		firstMouseEvent = false;
		return;
	}

	if (!camera)
		return;

	float deltaX = (posX - lastMouseX);
	float deltaY = (lastMouseY - posY);

	lastMouseX = posX;
	lastMouseY = posY;

	camera->processMouseMovement(deltaX, deltaY);
}

void updateCamera()
{
	if (!camera)
		return;

	if (pressed_keys[GLFW_KEY_W])
	{
		camera->processKeyboard(Camera::CameraDirection::FORWARD, 0.01666);
	}

	if (pressed_keys[GLFW_KEY_S])
	{
		camera->processKeyboard(Camera::CameraDirection::BACKWARD, 0.01666);
	}

	if (pressed_keys[GLFW_KEY_A])
	{
		camera->processKeyboard(Camera::CameraDirection::LEFT, 0.01666);
	}

	if (pressed_keys[GLFW_KEY_D])
	{
		camera->processKeyboard(Camera::CameraDirection::RIGHT, 0.01666);
	}
}

int main()
{
	// init glfw
	// ---------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create new window
	// -----------------
	GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// init glad
	// ---------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -2;
	}

	// enable depth test
	// -----------------
	glEnable(GL_DEPTH_TEST);

	// handle resize
	// -------------
	g_width = 800;
	g_height = 600;
	glViewport(0, 0, g_width, g_height);
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	// handle mouse events
	// -------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	// create shader
	// -------------
	Shader shader("../shaders/8_colors_vs.glsl", "../shaders/8_colors_fs.glsl");

	// prepare rendering data
	// ----------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(shader.getAttributeLocation("aPos"));
	glVertexAttribPointer(shader.getAttributeLocation("aPos"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// main loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// Input handler
		// -------------
		handleInput(window);

		// Update camera
		// -------------
		updateCamera();

		// Rendering
		// ---------
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		// view and projection matrices
		glm::mat4 view;
		view = camera->getViewMatrix();
		shader.setUniformMatrix4fv("View", 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 projection;
		projection = camera->getProjectionMatrix();
		shader.setUniformMatrix4fv("Projection", 1, GL_FALSE, glm::value_ptr(projection));

		// model matrix
		{
			glm::vec3 cubePositions[] = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};

			for (int i = 0; i < 10; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, glm::radians(20.0f * (i + 1) * (float)glfwGetTime()), glm::vec3(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime())));
				shader.setUniformMatrix4fv("Model", 1, GL_FALSE, glm::value_ptr(model));

				shader.setUniform3f("lightColor", 1.0, 1.0, 1.0);
				shader.setUniform3f("objectColor", 1.0, 0.6, 0.3);

				glBindVertexArray(vao);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		// Swap buffers and poll IO events (keys pressed/released, mouse moved, ...)
		// -------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	system("pause");
	return 0;
}