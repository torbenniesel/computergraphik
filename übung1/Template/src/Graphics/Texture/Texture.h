#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <assimp/scene.h>

class Texture
{
public:
	Texture();
	Texture(std::string filepath, aiTextureType type);
	Texture(std::string dir, std::string path, aiTextureType type);

	void Generate();
	void Load(bool flip = true);

	void Bind();

	unsigned int id;
	aiTextureType type;
	std::string path;
	std::string filepath;
};
#endif

