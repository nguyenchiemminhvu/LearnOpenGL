#include "Shader.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	std::ifstream vShaderFile, fShaderFile;
	std::stringstream ssVertex, ssFragment;
	std::string vShaderSource, fShaderSource;

	vShaderFile.open(vertexPath);
	ssVertex << vShaderFile.rdbuf();
	vShaderSource = ssVertex.str();
	vShaderFile.close();

	fShaderFile.open(fragmentPath);
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

	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &shaderStatus);
	if (!shaderStatus)
	{
		glGetProgramInfoLog(program, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED::" << logInfo << std::endl;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader()
{

}

GLint Shader::getAttributeLocation(const char * name)
{
	return glGetAttribLocation(program, name);
}

void Shader::enableAttribute(const char * name)
{
	glEnableVertexAttribArray(getAttributeLocation(name));
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::deleteShader()
{
	glDeleteProgram(program);
}

void Shader::setUniform1i(const char * name, GLint v0)
{
	glUniform1i(glGetUniformLocation(program, name), v0);
}

void Shader::setUniform1f(const char * name, GLfloat v0)
{
	glUniform1f(glGetUniformLocation(program, name), v0);
}

void Shader::setUniform1iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform1iv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform1fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform1fv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform2i(const char * name, GLint x, GLint y)
{
	glUniform2i(glGetUniformLocation(program, name), x, y);
}

void Shader::setUniform2f(const char * name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(program, name), x, y);
}

void Shader::setUniform2iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform2iv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform2fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform2fv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform3i(const char * name, GLint x, GLint y, GLint z)
{
	glUniform3i(glGetUniformLocation(program, name), x, y, z);
}

void Shader::setUniform3f(const char * name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(program, name), x, y, z);
}

void Shader::setUniform3iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform3iv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform3fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform3fv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform4i(const char * name, GLint x, GLint y, GLint z, GLint w)
{
	glUniform4i(glGetUniformLocation(program, name), x, y, z, w);
}

void Shader::setUniform4f(const char * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
}

void Shader::setUniform4iv(const char * name, GLsizei count, const GLint * value)
{
	glUniform4iv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniform4fv(const char * name, GLsizei count, const GLfloat * value)
{
	glUniform4fv(glGetUniformLocation(program, name), count, value);
}

void Shader::setUniformMatrix2fv(const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix2fv(glGetUniformLocation(program, name), count, transpose, value);
}

void Shader::setUniformMatrix3fv(const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix3fv(glGetUniformLocation(program, name), count, transpose, value);
}

void Shader::setUniformMatrix4fv(const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name), count, transpose, value);
}