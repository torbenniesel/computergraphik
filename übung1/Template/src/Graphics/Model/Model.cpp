#include "Graphics/Model/Model.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, bool noTex) :
	noTex(noTex),
	pos(pos),
	size(size),
	rotation(rotation),
	material(Material::white_plastic)
{
}

Model::Model(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, bool noTex, Material material) :
	noTex(noTex),
	pos(pos),
	size(size),
	rotation(rotation),
	material(material)
{
}

Model::Model(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, bool noTex, aiColor4D color) :
	noTex(noTex),
	pos(pos),
	size(size),
	rotation(rotation)
{
	this->SetColor(color);
}

Model::~Model()
{
	this->Cleanup();
}

void Model::Render(Shader shader, glm::mat4 modelMatrix, Material material) {
	this->material = material;
	this->Render(shader, modelMatrix);
}

void Model::Render(Shader shader, glm::mat4 modelMatrix)
{
	//accumulate the local transformations to generate the final model-matrix
	glm::mat4 trans = glm::mat4(modelMatrix);
	trans = glm::translate(trans, pos);
	trans = glm::scale(trans, size);
	if (rotation.x != 0) {
		trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	}
	if (rotation.y != 0) {
		trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	}
	if (rotation.z != 0) {
		trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	}

	shader.SetMat4("model", trans);

	shader.Set4Float("material.ambient", material.ambient);
	shader.Set4Float("material.diffuse", material.diffuse);
	shader.Set4Float("material.specular", material.specular);
	shader.Set4Float("material.emission", material.emission);
	shader.SetFloat("material.shininess", material.shininess);

	//for (Mesh mesh : meshes) {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		//mesh.Render(shader, pos, size, rotation);
		meshes[i].Render(shader, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	}

	shader.SetMat4("model", modelMatrix);
}

void Model::Cleanup()
{
	for (Mesh mesh : meshes) {
		mesh.Cleanup();
	}
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(
		path,
		/*aiProcess_RemoveComponent |
		aiProcess_RemoveRedundantMaterials |*/
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Could not load model at " << path << std::endl << import.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of("/"));
	ProcessNode(scene->mRootNode, scene);
}

void Model::AddMesh(Mesh mesh)
{
	meshes.push_back(mesh);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if (mesh->mTextureCoords[0] != NULL) {
			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else {
			vertex.texCoord = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh m;

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		if (mesh->mTextureCoords[0] == NULL)
			noTex = true;

		{
			// ambient color
			aiColor4D amb(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &amb);

			//diffuse color
			aiColor4D diff(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diff);

			//specular color
			aiColor4D spec(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &spec);

			//emission color
			aiColor4D emis(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emis);

			// shininess
			float shine(0);
			aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shine);

			m = Mesh(vertices, indices, amb, diff, spec, shine, emis);
			m.EnableLocalMaterial();
		}

		if (mesh->mTextureCoords[0]) {
			std::vector<Texture> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = LoadTextures(material, aiTextureType_SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

			m = Mesh(vertices, indices, textures);
		}
	}
	return m;
}

std::vector<Texture> Model::LoadTextures(aiMaterial* mat, aiTextureType type)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			std::cout << str.C_Str() << std::endl;
			Texture tex(directory, str.C_Str(), type);
			tex.Load(false);
			textures.push_back(tex);
			textures_loaded.push_back(tex);
		}
	}

	return textures;
}

void Model::SetMaterial(Material material) {
	this->material = material;
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].DisableLocalMaterial();
}

void Model::SetEmission(float factor) {
	material.emission = material.diffuse * factor;
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].DisableLocalMaterial();
}

void Model::ResetEmission() {
	material.emission = glm::vec4(0, 0, 0, 1.0f);
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].DisableLocalMaterial();
}

void Model::SetColor(aiColor4D color) {
	material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
	material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
	material.specular = glm::vec4(color.r, color.g, color.b, color.a);
	material.emission = glm::vec4(0, 0, 0, 1.0f);
	material.shininess = 0.5f;
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].DisableLocalMaterial();
}

void Model::SetAlpha(float factor) {
	material.ambient.a = material.ambient.a * factor;
	material.diffuse.a = material.diffuse.a * factor;
	material.specular.a = material.specular.a * factor;
	material.emission.a = material.emission.a * factor;
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].DisableLocalMaterial();
}

void Model::ResetAlpha() {
	material.ambient.a = 1.0f;
	material.diffuse.a = 1.0f;
	material.specular.a = 1.0f;
	material.emission.a = 1.0f;
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].DisableLocalMaterial();
}

//Adding position and rotation capabilities
// Setters
void Model::SetPosition(const glm::vec3& newPosition) {
	pos = newPosition;
}

void Model::SetRotation(const glm::vec3& newRotation) {
	rotation = newRotation;
}

void Model::SetSize(const glm::vec3& newSize) {
	size = newSize;
}

// Getters
glm::vec3 Model::GetPosition() const {
	return pos;
}

glm::vec3 Model::GetRotation() const {
	return rotation;
}

glm::vec3 Model::GetSize() const {
	return size;
}

// Methods for incremental updates
void Model::Translate(const glm::vec3& translation) {
	pos += translation;
}

void Model::Rotate(const glm::vec3& rot) {
	rotation += rot;
}