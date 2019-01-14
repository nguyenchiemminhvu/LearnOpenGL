#pragma once

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

#include <string>
#include <map>

class Material
{
public:

	std::string name;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material();
	Material(std::string name, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float sh);
	~Material();
};

class MaterialFactory
{
public:

	static std::map<std::string, Material> materials;

	static void make();

	static Material getMaterial(std::string &name);

};

#endif // __MATERIAL_H__