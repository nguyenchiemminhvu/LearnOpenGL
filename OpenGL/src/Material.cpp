#include "Material.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


Material::Material()
{

}


Material::Material(std::string name, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float sh)
	: name(name), ambient(amb), diffuse(diff), specular(spec), shininess(sh)
{

}


Material::~Material()
{

}


std::map<std::string, Material> MaterialFactory::materials = std::map<std::string, Material>();

void MaterialFactory::make()
{
	std::ifstream file("../resources/materials.dat");
	if (file.fail())
	{
		std::cout << "Can not read materials data" << std::endl;
	}

	while (!file.eof())
	{
		char temp[255];
		file.getline(temp, 255);
		std::stringstream ss(temp);
	
		std::string name;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

		ss >> name;
		ss >> ambient.r >> ambient.g >> ambient.b;
		ss >> diffuse.r >> diffuse.g >> diffuse.b;
		ss >> specular.r >> specular.g >> specular.b;
		ss >> shininess;

		materials[name] = Material(name, ambient, diffuse, specular, shininess);
	}

	file.close();
}


Material MaterialFactory::getMaterial(std::string & name)
{
	if (materials.find(name) != materials.end())
	{
		return materials[name];
	}

	return Material(name, glm::vec3(), glm::vec3(), glm::vec3(), 0.0);
}
