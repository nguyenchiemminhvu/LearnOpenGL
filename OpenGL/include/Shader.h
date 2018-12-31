#ifndef __SHADER_H__
#define __SHADER_H__

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	unsigned int program;

	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	~Shader();

	GLint getAttributeLocation(const char *name);

	void use();
	void deleteShader();

	// uniform utilities
	// -----------------
	void setUniform1i(const char *name, GLint v0);
	void setUniform1f(const char *name, GLfloat v0);
	void setUniform1iv(const char *name, GLsizei count, const GLint *value);
	void setUniform1fv(const char *name, GLsizei count, const GLfloat *value);
	
	void setUniform2i(const char *name, GLint x, GLint y);
	void setUniform2f(const char *name, GLfloat x, GLfloat y);
	void setUniform2iv(const char *name, GLsizei count, const GLint *value);
	void setUniform2fv(const char *name, GLsizei count, const GLfloat *value);

	void setUniform3i(const char *name, GLint x, GLint y, GLint z);
	void setUniform3f(const char *name, GLfloat x, GLfloat y, GLfloat z);
	void setUniform3iv(const char *name, GLsizei count, const GLint *value);
	void setUniform3fv(const char *name, GLsizei count, const GLfloat *value);

	void setUniform4i(const char *name, GLint x, GLint y, GLint z, GLint w);
	void setUniform4f(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setUniform4iv(const char *name, GLsizei count, const GLint *value);
	void setUniform4fv(const char *name, GLsizei count, const GLfloat *value);

	void setUniformMatrix2fv(const char *name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniformMatrix3fv(const char *name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniformMatrix4fv(const char *name, GLsizei count, GLboolean transpose, const GLfloat *value);
};

#endif // __SHADER_H__