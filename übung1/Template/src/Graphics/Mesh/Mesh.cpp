#include "Graphics/Mesh/Mesh.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

std::vector<Vertex> Vertex::genListVertex(float* vertices, int numberVertices)
{
	std::vector<Vertex> tmp(numberVertices);
	int stride = sizeof(Vertex) / sizeof(float);

	for (int i = 0; i < numberVertices; i++) {
		tmp[i].pos = glm::vec3(vertices[i * stride + 0], vertices[i * stride + 1], vertices[i * stride + 2]);
		tmp[i].normal = glm::vec3(vertices[i * stride + 3], vertices[i * stride + 4], vertices[i * stride + 5]);
		tmp[i].texCoord = glm::vec2(vertices[i * stride + 6], vertices[i * stride + 7]);
	}
	return tmp;
}

std::vector<unsigned int> Vertex::genListIndex(unsigned int* indices, int numberIndices)
{
	std::vector<unsigned int> tmp(numberIndices);
	for (int i = 0; i < numberIndices; i++) {
		tmp[i] = indices[i];
	}
	return tmp;
}

Mesh::Mesh() :
	material(Material::white_plastic),
	renderFormat(GL_TRIANGLES),
	initialized(false),
	useLocalMat(false),
	useTex(false)
{
}

Mesh::Mesh
(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	aiColor4D diffuse,
	aiColor4D specular,
	int RenderFormat
)
	:
	vertices(vertices),
	indices(indices),
	textures(),
	useTex(false),
	useLocalMat(false),
	renderFormat(RenderFormat),
	initialized(false)
{
	material.ambient = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	material.diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	material.specular = glm::vec4(specular.r, specular.g, specular.b, specular.a);
	material.emission = glm::vec4(0, 0, 0, 1.0f);
	material.shininess = 0.5f;
}

Mesh::Mesh
(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	aiColor4D diffuse,
	aiColor4D specular,
	aiColor4D emission,
	int RenderFormat
)
	:
	vertices(vertices),
	indices(indices),
	textures(),
	useTex(false),
	useLocalMat(true),
	renderFormat(RenderFormat),
	initialized(false)
{
	material.ambient = glm::vec4(diffuse.r * 0.1f, diffuse.g * 0.1f, diffuse.b * 0.1f, diffuse.a);
	material.diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	material.specular = glm::vec4(specular.r, specular.g, specular.b, specular.a);
	material.emission = glm::vec4(emission.r, emission.g, emission.b, emission.a);
	material.shininess = 0.5f;
}

Mesh::Mesh
(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	aiColor4D ambient,
	aiColor4D diffuse,
	aiColor4D specular,
	float shininess,
	aiColor4D emission,
	int RenderFormat
)
	:
	vertices(vertices),
	indices(indices),
	textures(),
	useTex(false),
	useLocalMat(true),
	renderFormat(RenderFormat),
	initialized(false)
{
	material.diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	material.ambient = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	material.specular = glm::vec4(specular.r, specular.g, specular.b, specular.a);
	material.emission = glm::vec4(emission.r, emission.g, emission.b, emission.a);
	material.shininess = 0.5f;
}

Mesh::Mesh
(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	aiColor4D color,
	int RenderFormat
)
	:
	vertices(vertices),
	indices(indices),
	textures(),
	useTex(false),
	useLocalMat(true),
	renderFormat(RenderFormat),
	initialized(false)
{
	material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
	material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
	material.specular = glm::vec4(color.r, color.g, color.b, color.a);
	material.emission = glm::vec4(0, 0, 0, 1.0f);
	material.shininess = 0.5f;
}

Mesh::Mesh
(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	Material _material,
	int RenderFormat
)
	:
	vertices(vertices),
	indices(indices),
	textures(),
	useTex(false),
	useLocalMat(true),
	renderFormat(RenderFormat),
	initialized(false)
{
	material = _material;
}

Mesh::Mesh
(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	std::vector<Texture> textures,
	int RenderFormat
)
	:
	vertices(vertices),
	indices(indices),
	textures(textures),
	useTex(true),
	useLocalMat(false),
	renderFormat(RenderFormat),
	initialized(false)
{
	material = Material::white_plastic;
}

void Mesh::SetEmission(float factor) {
	material.emission = material.diffuse * factor;
};
void Mesh::ResetEmission() {
	material.emission = glm::vec4(0, 0, 0, 1.0f);
};

void Mesh::Render(Shader shader, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation)
{
	if (!initialized) {
		initialized = true;
		glm::mat4 tmp = glm::mat4(1.0f);
		tmp = glm::translate(tmp, pos);
		tmp = glm::scale(tmp, size);
		if (rotation.x != 0) {
			tmp = glm::rotate(tmp, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		}
		if (rotation.y != 0) {
			tmp = glm::rotate(tmp, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		}
		if (rotation.z != 0) {
			tmp = glm::rotate(tmp, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		}
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].pos = tmp * glm::vec4(vertices[i].pos, 1.0f);
			vertices[i].normal = glm::transpose(glm::inverse(tmp)) * glm::vec4(vertices[i].normal, 1.0f);
		}
		Setup();
	}

	if (useLocalMat) { // initialize the uniform material variables in the shader
		shader.Set4Float("material.ambient", material.ambient);
		shader.Set4Float("material.diffuse", material.diffuse);
		shader.Set4Float("material.specular", material.specular);
		shader.Set4Float("material.emission", material.emission);
		shader.SetFloat("material.shininess", material.shininess);
	}

	if (useTex) {
		shader.SetInt("useTex", 1);
		shader.SetInt("hasDiffMap", 0);
		shader.SetInt("hasSpecMap", 0);

		unsigned int diffuseIdx = 0;
		unsigned int specularIdx = 0;

		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);

			std::string name;
			switch (textures[i].type)
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuseIdx++);
				shader.SetInt("hasDiffMap", 1);
				break;
			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specularIdx++);
				shader.SetInt("hasSpecMap", 1);
				break;
			default:
				break;
			}

			shader.SetInt(name, i);
			textures[i].Bind();
		}
	}
	else {
		shader.SetInt("useTex", 0);
		shader.SetInt("hasDiffMap", 0);
		shader.SetInt("hasSpecMap", 0);
	}

	vertexArray.Bind();
	glDrawElements(renderFormat, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Cleanup()
{
	vertexArray.Cleanup();
	indexBuffer.Cleanup();
	vertexBuffer.Cleanup();
}

void Mesh::Setup()
{
	this->vertexBuffer = VertexBuffer();
	this->layout = VertexBufferLayout();
	this->indexBuffer = IndexBuffer();
	this->vertexArray = VertexArray();

	this->vertexBuffer.NewData(&vertices[0], sizeof(Vertex) * (GLsizei)vertices.size());
	layout.Push<glm::vec3>(1);
	layout.Push<glm::vec3>(1);
	layout.Push<glm::vec2>(1);
	this->vertexArray.AddBuffer(vertexBuffer, layout);

	//std::cout << "VerticeSize: " << vertices.size() << " IndiceSize: " << indices.size() << std::endl;

	this->indexBuffer.NewData(&indices[0], (GLsizei)indices.size());
}
