#ifndef COORDINATESYSTEM_HPP
#define COORDINATESYSTEM_HPP

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

class COSAxles : public Model {
public:
	COSAxles(
		float minX = 0, float maxX = 0, float minY = 0,
		float maxY = 0, float minZ = 0, float maxZ = 0,
		glm::vec3 pos = glm::vec3(0.0f),
		glm::vec3 size = glm::vec3(1.0f))
		: Model(pos, size, glm::vec3(0.0f), true)
	{
		init(minX, maxX, minY, maxY, minZ, maxZ);
	}

	void init(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		vertices.push_back(Vertex(glm::vec3(minX, 0, 0), glm::vec3(0.0f), glm::vec2(0.0f)));
		vertices.push_back(Vertex(glm::vec3(maxX, 0, 0), glm::vec3(0.0f), glm::vec2(0.0f)));

		for (float i = minX; i <= maxX; i++) {
			vertices.push_back(Vertex(glm::vec3(i, -0.15f, 0), glm::vec3(0.0f), glm::vec2(0.0f)));
			vertices.push_back(Vertex(glm::vec3(i, 0.15f, 0), glm::vec3(0.0f), glm::vec2(0.0f)));
		}

		for (unsigned int i = 0; i < vertices.size(); i++) {
			indices.push_back(i);
		}

		meshes.push_back(Mesh(vertices, indices, Color::red, Color::red, Color::red, GL_LINES));
		vertices.clear();

		vertices.push_back(Vertex(glm::vec3(0, minX, 0), glm::vec3(0.0f), glm::vec2(0.0f)));
		vertices.push_back(Vertex(glm::vec3(0, maxX, 0), glm::vec3(0.0f), glm::vec2(0.0f)));

		for (float i = minY; i <= maxY; i++) {
			vertices.push_back(Vertex(glm::vec3(-0.15f, i, 0), glm::vec3(0.0f), glm::vec2(0.0f)));
			vertices.push_back(Vertex(glm::vec3(0.15f, i, 0), glm::vec3(0.0f), glm::vec2(0.0f)));
		}

		meshes.push_back(Mesh(vertices, indices, Color::green, Color::green, Color::green, GL_LINES));
		vertices.clear();

		vertices.push_back(Vertex(glm::vec3(0, 0, minZ), glm::vec3(0.0f), glm::vec2(0.0f)));
		vertices.push_back(Vertex(glm::vec3(0, 0, maxZ), glm::vec3(0.0f), glm::vec2(0.0f)));

		for (float i = minZ; i <= maxZ; i++) {
			vertices.push_back(Vertex(glm::vec3(-0.15f, 0, i), glm::vec3(0.0f), glm::vec2(0.0f)));
			vertices.push_back(Vertex(glm::vec3(0.15f, 0, i), glm::vec3(0.0f), glm::vec2(0.0f)));
		}

		meshes.push_back(Mesh(vertices, indices, Color::blue, Color::blue, Color::blue, GL_LINES));
	}

	void Render(Shader shader, glm::mat4 modelMatrix) {
		Model::Render(shader, modelMatrix);
	}

};
#endif