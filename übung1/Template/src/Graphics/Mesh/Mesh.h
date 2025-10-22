#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Graphics/Material/Material.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/VertexBufferLayout.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Texture/Texture.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;

	Vertex(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 normal = glm::vec3(0.0f), glm::vec2 texCoord = glm::vec2(0.0f)) : pos(pos), normal(normal), texCoord(texCoord) {}
	static std::vector<struct Vertex> genListVertex(float* vertices, int numberVertices);
	static std::vector<unsigned int> genListIndex(unsigned int* indices, int numberIndices);
};
typedef struct Vertex Vertex;

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	std::vector<Texture> textures;
	Material material;

	Mesh();
	Mesh(
		std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices, 
		aiColor4D diffuse, 
		aiColor4D specular, 
		int renderFormat = GL_TRIANGLES
	);
	Mesh(
		std::vector<Vertex> vertices,
		std::vector<unsigned int> indices,
		aiColor4D diffuse,
		aiColor4D specular,
		aiColor4D emission,
		int renderFormat = GL_TRIANGLES
	);

	Mesh(
		std::vector<Vertex> vertices,
		std::vector<unsigned int> indices,
		aiColor4D ambient,
		aiColor4D diffuse,
		aiColor4D specular,
		float shininess,
		aiColor4D emission,
		int renderFormat = GL_TRIANGLES
	);

	Mesh(
		std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices, 
		aiColor4D color, 
		int renderFormat = GL_TRIANGLES
	);
	Mesh(
		std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices, 
		Material _material, 
		int renderFormat = GL_TRIANGLES
	);
	Mesh(
		std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices, 
		std::vector<Texture> textures = {}, 
		int renderFormat = GL_TRIANGLES
	);

	void Render(Shader shader, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation);

	void SetEmission(float factor = 1.0f);
	void ResetEmission();

	void EnableLocalMaterial() { useLocalMat = true; }
	void DisableLocalMaterial() { useLocalMat = false; }

	void Cleanup();
private:
	bool useTex; // if true then the render function enables texturing and sets the uniforms
	bool useLocalMat; // if true then the render function sets the material
	bool initialized;

	int renderFormat;

	VertexBuffer vertexBuffer;
	VertexBufferLayout layout;
	IndexBuffer indexBuffer;
	VertexArray vertexArray;

	void Setup();
};
#endif

