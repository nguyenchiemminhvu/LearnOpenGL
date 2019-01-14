#include "Material.h"

#include <iostream>
#include <fstream>
#include <sstream>


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

		Material mat(name, ambient, diffuse, specular, shininess);
		materials.insert(std::pair<std::string, Material>(name, mat));
	}

	file.close();
}


Material MaterialFactory::getMaterial(std::string & name)
{


	return Material(name, glm::vec3(), glm::vec3(), glm::vec3(), 0.0);
}
