#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Graphics/Mesh/Mesh.h"

class Model
{
public:
	Model(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f), bool noTex = false);
	Model(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, bool noTex, Material material);
	Model(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, bool noTex, aiColor4D color);
	~Model();

	void Render(Shader shader, glm::mat4 modelMatrix);
	void Render(Shader shader, glm::mat4 modelMatrix, Material material);

	void Cleanup();

	void LoadModel(std::string path);

	void AddMesh(Mesh mesh);

	void SetMaterial(Material material);
	void SetEmission(float factor = 1.0f);
	void ResetEmission();
	void SetColor(aiColor4D color);

	void SetAlpha(float factor = 1.0f);
	void ResetAlpha();


protected:
	bool noTex;
	Material material;

	glm::vec3 pos;
	glm::vec3 size; 
	glm::vec3 rotation;

	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> textures_loaded;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType type);
};
#endif

