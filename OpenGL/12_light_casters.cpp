#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

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

	// handle mouse events
	// -------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

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
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers and poll IO events (keys pressed/released, mouse moved, ...)
		// -------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	system("pause");
	return 0;
}