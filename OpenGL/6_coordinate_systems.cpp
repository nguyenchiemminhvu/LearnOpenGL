#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Shader.h"

#include <iostream>

#define NUM_KEYS 512
bool pressed_keys[NUM_KEYS] = { false };

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

	// handle resize
	// -------------
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	// enable depth test
	// -----------------
	glEnable(GL_DEPTH_TEST);

	// handle mouse events
	// -------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	// create shader
	// -------------
	Shader shader("../shaders/6_coordinate_systems_vs.glsl", "../shaders/6_coordinate_systems_fs.glsl");

	// create texture
	// --------------
	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, channels;
	unsigned char *texData = SOIL_load_image("../textures/container.jpg", &width, &height, &channels, 0);
	if (texData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	SOIL_free_image_data(texData);
	glBindTexture(GL_TEXTURE_2D, 0);

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
	glEnableVertexAttribArray(shader.getAttributeLocation("aUV"));
	glVertexAttribPointer(shader.getAttributeLocation("aUV"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// main loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// Input handler
		// -------------
		handleInput(window);

		// Rendering
		// ---------
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glActiveTexture(GL_TEXTURE0 + texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader.setUniform1i("tex", texID);

		// view and projection matrices
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		shader.setUniformMatrix4fv("View", 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(51.0), 800.0 / 600.0, 0.1, 100.0);
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