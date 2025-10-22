#ifndef CUBE_HPP
#define CUBE_HPP

#include <string>

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

class Cube : public Model {
public:

	bool noMat;
	float sideLength;
	std::vector<std::string> texturepaths;
	std::vector<aiTextureType> types;

	/// <summary>
	/// Create a cube centered at the origin.
	/// </summary>
	/// <param name="width"> The width, height and depth of the cube. </param>
	/// <param name="color"> Color of the cube, default = Color::blue </param>
	/// <remarks> The constructor generates a cube with side-length given by <c>width</c>. The vertices of the cube are at (+/- width/2, +/- width/2, +/- width/2), so that the cube is centered at the origin. </remarks>
	Cube(float width = 1.0f, aiColor4D color = Color::blue) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
	{
		sideLength = width;
		material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
		material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
		material.specular = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
		material.shininess = 0.5f;
	}

	/// <summary>
	/// Create a cube
	/// </summary>
	/// <param name="width"> The width, height and depth of the cube. </param>
	/// <param name="color">Color of the cube</param>
	/// <param name="pos">Sets a translation for the center of the cube</param>
	/// <param name="size">Sets the edgelenth for each dimension of the cube</param>
	/// <param name="rotation">Sets the rotation of the cube around its center</param>
	/// <remarks> The constructor generates a cube with side-length given by <c>width</c>. The vertices of the cube are at (+/- width/2, +/- width/2, +/- width/2), so that the cube is centered at the origin. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
	Cube(float width, aiColor4D color, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(true)
	{
		sideLength = width;
		material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
		material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
		material.specular = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
		material.shininess = 0.5f;
		init();
	}

	/// <summary>
	/// Create a cube
	/// </summary>
	/// <param name="width"> The width, height and depth of the cube. </param>
	/// <param name="_material">Material-Definition of the cube, default = Material::white_plastic</param>
	/// <remarks> The constructor generates a cube with side-length given by <c>width</c>. The vertices of the cube are at (+/- width/2, +/- width/2, +/- width/2), so that the cube is centered at the origin. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
	Cube(float width, Material _material) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
	{
		sideLength = width;
		material = _material;
		init();
	}

	/// <summary>
	/// Create a cube
	/// </summary>
	/// <param name="width"> The width, height and depth of the cube. </param>
	/// <param name="_material">Material-Definition of the cube</param>
	/// <param name="pos">Sets a translation for the center of the cube</param>
	/// <param name="size">Sets the edgelenth for each dimension of the cube</param>
	/// <param name="rotation">Sets the rotation of the cube around its center</param>
	/// <remarks> The constructor generates a cube with side-length given by <c>width</c>. The vertices of the cube are at (+/- width/2, +/- width/2, +/- width/2), so that the cube is centered at the origin. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
	Cube(float width, Material _material, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(false)
	{
		sideLength = width;
		material = _material;
		init();
	}

	/// <summary>
	/// Create a cube
	/// </summary>
	/// <param name="width"> The width, height and depth of the cube. </param>
	/// <param name="texturepaths">List of filepaths for images used as textures</param>
	/// <param name="types">List of assoziated texture-types</param>
	/// <param name="pos">Sets a translation for the center of the cube</param>
	/// <param name="size">Sets the edgelenth for each dimension of the cube</param>
	/// <param name="rotation">Sets the rotation of the cube around its center</param>
	/// <remarks> The constructor generates a cube with side-length given by <c>width</c>. The vertices of the cube are at (+/- width/2, +/- width/2, +/- width/2), so that the cube is centered at the origin. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
	Cube(float width, std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types), noMat(false)
	{
		material = Material::white_plastic;
		sideLength = width;
		init();
	}

	void init() {
		int numberVertices = 36;
		float halfExtend = sideLength / 2.0f;
		float vertices[] = {
			// position                                      normal            texcoord

			// front
			-halfExtend, -halfExtend,  halfExtend,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
			 halfExtend, -halfExtend,  halfExtend,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
			 halfExtend,  halfExtend,  halfExtend,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			 halfExtend,  halfExtend,  halfExtend,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			-halfExtend,  halfExtend,  halfExtend,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
			-halfExtend, -halfExtend,  halfExtend,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,

			// back
			-halfExtend, -halfExtend, -halfExtend,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
			 halfExtend,  halfExtend, -halfExtend,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			 halfExtend, -halfExtend, -halfExtend,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
			 halfExtend,  halfExtend, -halfExtend,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			-halfExtend, -halfExtend, -halfExtend,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
			-halfExtend,  halfExtend, -halfExtend,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
			
			// left
			-halfExtend,  halfExtend,  halfExtend,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			-halfExtend,  halfExtend, -halfExtend,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			-halfExtend, -halfExtend, -halfExtend,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			-halfExtend, -halfExtend, -halfExtend,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			-halfExtend, -halfExtend,  halfExtend,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			-halfExtend,  halfExtend,  halfExtend,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

			// right 
			 halfExtend,  halfExtend,  halfExtend,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			 halfExtend, -halfExtend, -halfExtend,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			 halfExtend,  halfExtend, -halfExtend,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			 halfExtend, -halfExtend, -halfExtend,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			 halfExtend,  halfExtend,  halfExtend,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			 halfExtend, -halfExtend,  halfExtend,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,

			// bottom
			-halfExtend, -halfExtend, -halfExtend,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
			 halfExtend, -halfExtend, -halfExtend,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
			 halfExtend, -halfExtend,  halfExtend,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
			 halfExtend, -halfExtend,  halfExtend,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
			-halfExtend, -halfExtend,  halfExtend,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
			-halfExtend, -halfExtend, -halfExtend,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

			// top
			-halfExtend,  halfExtend, -halfExtend,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
			 halfExtend,  halfExtend,  halfExtend,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			 halfExtend,  halfExtend, -halfExtend,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
			-halfExtend,  halfExtend,  halfExtend,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
			 halfExtend,  halfExtend,  halfExtend,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			-halfExtend,  halfExtend, -halfExtend,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
		};

		std::vector<unsigned int> indices(numberVertices);
		for (unsigned int i = 0; i < (unsigned int)numberVertices; i++) {
			indices[i] = i;
		}

		if (!texturepaths.empty()) {
			std::vector<Texture> textures;
			for (int i = 0; i < texturepaths.size(); i++) {
				Texture tmp(texturepaths[i], types[i]);
				tmp.Load();
				textures.push_back(tmp);
			}
			meshes.push_back(Mesh(Vertex::genListVertex(vertices, numberVertices), indices, textures));
		}
		else {
			meshes.push_back(Mesh(Vertex::genListVertex(vertices, numberVertices), indices, material));
		}
		meshes.back().DisableLocalMaterial();
	}
};
#endif