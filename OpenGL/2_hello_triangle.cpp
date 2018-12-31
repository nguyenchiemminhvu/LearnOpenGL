#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

	// prepare rendering data
	// ----------------------
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int vbo; // vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vao; // vertex array object (to layout data in vertex buffer object)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0); // location index of aPos in shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int ebo; // element buffer object
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// create shaders
	// --------------
	unsigned int shaderProgram;
	{
		std::ifstream vShaderFile, fShaderFile;
		std::stringstream ssVertex, ssFragment;
		std::string vShaderSource, fShaderSource;

		vShaderFile.open("../shaders/2_hello_triangle_vs.glsl");
		ssVertex << vShaderFile.rdbuf();
		vShaderSource = ssVertex.str();
		vShaderFile.close();

		fShaderFile.open("../shaders/2_hello_triangle_fs.glsl");
		ssFragment << fShaderFile.rdbuf();
		fShaderSource = ssFragment.str();
		fShaderFile.close();

		const char *vertexShader = vShaderSource.c_str();
		const char *fragShader = fShaderSource.c_str();

		unsigned int vShader;
		unsigned int fShader;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vShader, 1, &vertexShader, NULL);
		glShaderSource(fShader, 1, &fragShader, NULL);
		glCompileShader(vShader);
		glCompileShader(fShader);

		int shaderStatus;
		char logInfo[512];
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &shaderStatus);
		if (!shaderStatus)
		{
			glGetShaderInfoLog(vShader, 512, NULL, logInfo);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED::" << logInfo << std::endl;
		}
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &shaderStatus);
		if (!shaderStatus)
		{
			glGetShaderInfoLog(fShader, 512, NULL, logInfo);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED::" << logInfo << std::endl;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vShader);
		glAttachShader(shaderProgram, fShader);
		
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderStatus);
		if (!shaderStatus)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, logInfo);
			std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED::" << logInfo << std::endl;
		}

		glDeleteShader(vShader);
		glDeleteShader(fShader);
	}

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

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll IO events (keys pressed/released, mouse moved, ...)
		// -------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	system("pause");
	return 0;
}