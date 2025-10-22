#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

class Sphere : public Model {
public:
	bool noMat;
	std::vector<std::string> texturepaths;
	std::vector<aiTextureType> types;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	/// <summary>
	/// Draw a sphere.
	/// </summary>
	/// <param name="radius">The radius of the sphere.</param>
	/// <param name="slices">The number of subdivisions around the Z axis (similar to lines of longitude).</param>
	/// <param name="stacks">The number of subdivisions along the Z axis (similar to lines of latitude).</param>
	/// <param name="color">Color of the octahedron, default = Color::blue</param>
	/// <remarks> Renders a sphere centered at the modeling coordinates origin of the specified radius. The sphere is subdivided around the Z axis into slices and along the Z axis into stacks. </remarks>
	Sphere (
		float radius = 1.0f, 
		int slices = 20, 
		int stacks = 20, 
		aiColor4D color = Color::blue
	) : 
		Model (glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), 
		texturepaths(), 
		types(), 
		noMat(false)
	{
		material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
		material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
		material.specular = glm::vec4(color.r, color.g, color.b, color.a);
		material.shininess = 0.5f;
		init(radius, slices, stacks);
	}

	/// <summary>
	/// Draw a sphere.
	/// </summary>
	/// <param name="radius">The radius of the sphere.</param>
	/// <param name="slices">The number of subdivisions around the Z axis (similar to lines of longitude).</param>
	/// <param name="stacks">The number of subdivisions along the Z axis (similar to lines of latitude).</param>
	/// <param name="color">Color of the octahedron, default = Color::blue</param>
	/// <param name="pos">Sets a translation for the center of the sphere</param>
	/// <param name="size">Sets the extend for each dimension of the sphere</param>
	/// <param name="rotation">Sets the rotation of the sphere around its center</param>
	/// <remarks> Renders a sphere centered at the modeling coordinates origin of the specified radius. The sphere is subdivided around the Z axis into slices and along the Z axis into stacks. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
	Sphere (
		float radius, 
		int slices, 
		int stacks, 
		aiColor4D color, 
		glm::vec3 pos, 
		glm::vec3 size, 
		glm::vec3 rotation
	) : 
		Model (pos, size, rotation, true), texturepaths(), types(), noMat(false)
	{
		material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
		material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
		material.specular = glm::vec4(color.r, color.g, color.b, color.a);
		material.shininess = 0.5f;
		init(radius, slices, stacks);
	}

	/// <summary>
	/// Draw a sphere.
	/// </summary>
	/// <param name="radius">The radius of the sphere.</param>
	/// <param name="slices">The number of subdivisions around the Z axis (similar to lines of longitude).</param>
	/// <param name="stacks">The number of subdivisions along the Z axis (similar to lines of latitude).</param>
	/// <param name="_material">Material-Definition of the sphere</param>
	/// <remarks> Renders a sphere centered at the modeling coordinates origin of the specified radius. The sphere is subdivided around the Z axis into slices and along the Z axis into stacks. </remarks>
	Sphere (
		float radius, 
		int slices, 
		int stacks, 
		Material _material
	) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), 
		texturepaths(), 
		types(), 
		noMat(false)
	{
		material = _material;
		init(radius, slices, stacks);
	}


	/// <summary>
	/// Draw a sphere.
	/// </summary>
	/// <param name="radius">The radius of the sphere.</param>
	/// <param name="slices">The number of subdivisions around the Z axis (similar to lines of longitude).</param>
	/// <param name="stacks">The number of subdivisions along the Z axis (similar to lines of latitude).</param>
	/// <param name="_material">Material-Definition of the sphere</param>
	/// <param name="pos">Sets a translation for the center of the sphere</param>
	/// <param name="size">Sets the extend for each dimension of the sphere</param>
	/// <param name="rotation">Sets the rotation of the sphere around its center</param>
	/// <remarks> Renders a sphere centered at the modeling coordinates origin of the specified radius. The sphere is subdivided around the Z axis into slices and along the Z axis into stacks. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
	Sphere (
		float radius, 
		int slices, 
		int stacks, 
		Material _material, 
		glm::vec3 pos, 
		glm::vec3 size, 
		glm::vec3 rotation
	) : 
		Model(pos, size, rotation, true), 
		texturepaths(), 
		types(), 
		noMat(false)
	{
		material = _material;
		init(radius, slices, stacks);
	}


	/// <summary>
	/// Draw a sphere.
	/// </summary>
	/// <param name="radius">The radius of the sphere.</param>
	/// <param name="slices">The number of subdivisions around the Z axis (similar to lines of longitude).</param>
	/// <param name="stacks">The number of subdivisions along the Z axis (similar to lines of latitude).</param>
	/// <param name="texturepaths">List of filepaths for images used as textures</param>
	/// <param name="types">>List of assoziated texture-types</param>
	/// <param name="pos">Sets a translation for the center of the sphere</param>
	/// <param name="size">Sets the extend for each dimension of the sphere</param>
	/// <param name="rotation">Sets the rotation of the sphere around its center</param>
	/// <remarks> Renders a sphere centered at the modeling coordinates origin of the specified radius. The sphere is subdivided around the Z axis into slices and along the Z axis into stacks. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
	Sphere (
		float radius, 
		int slices, 
		int stacks, 
		std::vector<std::string> texturepaths, 
		std::vector<aiTextureType> types, 
		glm::vec3 pos = glm::vec3(0.0f), 
		glm::vec3 size = glm::vec3(1.0f), 
		glm::vec3 rotation = glm::vec3(0.0f)
	) : 
		Model(pos, size, rotation, false), 
		texturepaths(texturepaths), 
		types(types), 
		noMat(false)
	{
		material = Material::white_plastic;
		init(radius, slices, stacks);
	}

private:
	int numSlices;
	int numStacks;
	float radius;

	void init(float radius, int slices, int stacks) {

		this->numSlices = slices;
		this->numStacks = stacks;
		this->radius = radius;

		this->vertices.clear();
		this->indices.clear();

		generateSphere();

		if (!texturepaths.empty()) {
			std::vector<Texture> textures;
			for (int i = 0; i < texturepaths.size(); i++) {
				Texture tmp(texturepaths[i], types[i]);
				tmp.Load();
				textures.push_back(tmp);
			}
			meshes.push_back(Mesh(vertices, indices, textures));
		}
		else {
			meshes.push_back(Mesh(vertices, indices, material));
		}
		meshes.back().DisableLocalMaterial();
	}

	void generateSphere() {
		glm::vec3 pos;     
		glm::vec3 n;
		glm::vec2 texCoord;

		float rCosU;
		float sliceWidth = 2 * (float)M_PI / numSlices;
		float stackHight = (float)M_PI / numStacks;
		float sliceAngle;
		float stackAngle;

		// generate vertices using polar coordinates u, v
		for (int stack = 0; stack <= numStacks; ++stack)
		{
			// stack parameters
			stackAngle = (float)M_PI / 2.0f - stack * stackHight;
			rCosU = radius * cosf(stackAngle);		// radius * cos(u)
			float z = radius * sinf(stackAngle);	// radius * sin(u)

			// each stack has 1 additional vertex if sphere is textured !!
			// vertex split: 
			// first and last vertex share the same position BUT do have different!! text coords
			for (int slice = 0; slice <= numSlices; ++slice)
			{
				// slice paramters
				sliceAngle = slice * sliceWidth;

				// vertex generation
				// position, z from above
				pos.x = rCosU * cosf(sliceAngle);	// r * cos(u) * cos(v)
				pos.y = rCosU * sinf(sliceAngle);	// r * cos(u) * sin(v)
				pos.z = z;

				// normal, length = 1
				n = pos / radius;

				// vertex tex coord (s, t) range between [0, 1]
				texCoord.s = (float)slice / (float)numSlices;
				texCoord.t = (float)stack / (float)numStacks;

				// add to vertex array of sphere
				vertices.push_back(Vertex(pos, n, texCoord));
			}
		}

		// generate index array in ccw orientation
		// v1 --- v1+1
		// |    /   |
		// |   /    |
		// |  /     |
		// v2 --- v2+1
		int v1, v2;
		for (int stack = 0; stack < numStacks; ++stack)
		{
			v1 = stack * (numSlices + 1); // start at current stack
			v2 = v1 + numSlices + 1;      // end at next stack

			for (int slice = 0; slice < numSlices; ++slice, ++v1, ++v2)
			{
				// left triangle
				if (stack != 0)
				{
					indices.push_back(v1);
					indices.push_back(v2);
					indices.push_back(v1 + 1);
				}

				// right triangle
				if (stack != (numStacks - 1))
				{
					indices.push_back(v1 + 1);
					indices.push_back(v2);
					indices.push_back(v2 + 1);
				}
			}
		}
	}
};
#endif