#include "Graphics/Light/Light.h"
#include "Graphics/Models/Sphere.hpp"

void AmbientLight::Render(Shader shader)
{
	shader.Bind();
	shader.Set4Float("ambientLight", ambient);
}

void DirLight::Render(Shader shader, int idx)
{
	std::string name = "dirLights[" + std::to_string(idx) + "]";

	shader.SetInt(name + ".enabled", enabled);
	
	shader.Set3Float(name + ".direction", direction);

	shader.Set4Float(name + ".ambient", ambient);
	shader.Set4Float(name + ".diffuse", diffuse);
	shader.Set4Float(name + ".specular", specular);
}

void PointLight::Render(Shader shader, int idx)
{
	shader.Bind();
	std::string name = "pointLights[" + std::to_string(idx) + "]";

	shader.SetInt(name + ".enabled", enabled);

	shader.Set3Float(name + ".position", position);
		   
	shader.SetFloat(name + ".k0", k0);
	shader.SetFloat(name + ".k1", k1);
	shader.SetFloat(name + ".k2", k2);
		   
	shader.Set4Float(name + ".ambient", ambient);
	shader.Set4Float(name + ".diffuse", diffuse);
	shader.Set4Float(name + ".specular", specular);
}

void SpotLight::Render(Shader shader, int idx)
{
	std::string name = "spotLights[" + std::to_string(idx) + "]";

	shader.SetInt(name + ".enabled", enabled);

	shader.Set3Float(name + ".position", position);
	shader.Set3Float(name + ".direction", direction);
		   
	shader.SetFloat(name + ".k0", k0);
	shader.SetFloat(name + ".k1", k1);
	shader.SetFloat(name + ".k2", k2);
		   
	shader.SetFloat(name + ".cutOff", cutOff);
	shader.SetFloat(name + ".outerCutOff", outerCutOff);
		   
	shader.Set4Float(name + ".ambient", ambient);
	shader.Set4Float(name + ".diffuse", diffuse);
	shader.Set4Float(name + ".specular", specular);
}
