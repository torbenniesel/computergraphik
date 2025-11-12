#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "Graphics/Shader/Shader.h"

struct AmbientLight
{
	glm::vec4 ambient = glm::vec4(0, 0, 0, 1.0f);;
	void Render(Shader shader);
};

struct DirLight
{
	bool enabled = true;

	glm::vec3 direction = glm::vec3(0, 0, 1.0f);

	glm::vec4 ambient = glm::vec4(0, 0, 0, 1.0f);
	glm::vec4 diffuse = glm::vec4(0, 0, 0, 1.0f);
	glm::vec4 specular = glm::vec4(0, 0, 0, 1.0f);

	void Render(Shader shader) { Render(shader, 0); }
	void Render(Shader shader, int idx);
};

struct PointLight
{
	bool enabled = false;

	glm::vec3 position = glm::vec3(0, 0, 0);

	float k0 = 1.0f;
	float k1 = 0;
	float k2 = 0;

	glm::vec4 ambient = glm::vec4(0, 0, 0, 1.0f);
	glm::vec4 diffuse = glm::vec4(0, 0, 0, 1.0f);
	glm::vec4 specular = glm::vec4(0, 0, 0, 1.0f);

	void Render(Shader shader, int idx);
};

struct SpotLight
{
	bool enabled = false;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);

	float cutOff = 0;
	float outerCutOff = 0;
	
	float k0 = 1.0f;
	float k1 = 0;
	float k2 = 0;

	glm::vec4 ambient = glm::vec4(0, 0, 0, 1.0f);
	glm::vec4 diffuse = glm::vec4(0, 0, 0, 1.0f);
	glm::vec4 specular = glm::vec4(0, 0, 0, 1.0f);

	void Render(Shader shader, int idx);
};
#endif

