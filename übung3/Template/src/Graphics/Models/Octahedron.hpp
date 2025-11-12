#ifndef OCTAHEDRON_HPP
#define OCTAHEDRON_HPP

#include <string>

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

class Octahedron : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    /// <summary>
    /// Create a octahedron (8-sided regular solid)
    /// </summary>
    /// <param name="color">Color of the octahedron, default = Color::blue</param>
    /// <remarks> The octahedron is centered at the modeling coordinates origin with a radius of 1.0. </remarks>
    Octahedron(aiColor4D color = Color::blue) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Create a octahedron (8-sided regular solid)
    /// </summary>
    /// <param name="color">Color of the octahedron</param>
    /// <param name="pos">Sets a translation for the center of the octahedron</param>
    /// <param name="size">Sets the extend for each dimension of the octahedron</param>
    /// <param name="rotation">Sets the rotation of the octahedron around its center</param>
    /// <remarks> The octahedron is centered at the modeling coordinates origin with a radius of 1.0. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
    Octahedron(aiColor4D color, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(true)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Create a octahedron (8-sided regular solid)
    /// </summary>
    /// <param name="_material">Material-Definition of the octahedron</param>
    /// <remarks> The octahedron is centered at the modeling coordinates origin with a radius of 1.0.</remarks>
    Octahedron(Material _material) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }

    /// <summary>
    /// Create a octahedron (8-sided regular solid)
    /// </summary>
    /// <param name="_material">Material-Definition of the octahedron</param>
    /// <param name="pos">Sets a translation for the center of the octahedron</param>
    /// <param name="size">Sets the extend for each dimension of the octahedron</param>
    /// <param name="rotation">Sets the rotation of the octahedron around its center</param>
    /// <remarks> The octahedron is centered at the modeling coordinates origin with a radius of 1.0. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
    Octahedron(Material _material, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }

    /// <summary>
    /// Create a octahedron (8-sided regular solid)
    /// </summary>
    /// <param name="texturepaths">List of filepaths for images used as textures</param>
    /// <param name="types">List of assoziated texture-types</param>
    /// <param name="pos">Sets a translation for the center of the octahedron</param>
    /// <param name="size">Sets the extend for each dimension of the octahedron</param>
    /// <param name="rotation">Sets the rotation of the octahedron around its center</param>
    /// <remarks> The octahedron is centered at the modeling coordinates origin with a radius of 1.0. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
    Octahedron(std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types), noMat(false) 
    { 
        material = Material::white_plastic;
        init(); 
    }

    

    

	void init() {
        int numberVertices = 6;
        float vertices[] = {
            // position              normal                 texcoord
            -1.0f,  0.0f,  0.0f,     -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
             0.0f, -1.0f,  0.0f,      0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
             1.0f,  0.0f,  0.0f,      1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
             0.0f,  1.0f,  0.0f,      0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
             0.0f,  0.0f,  1.0f,      0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
             0.0f,  0.0f, -1.0f,      0.0f,  0.0f, -1.0f,   0.0f, 0.0f
        };

        int numberIndices = 24;
        unsigned int indices[] = {
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            0, 4, 3,
            5, 1, 0,
            5, 2, 1,
            5, 3, 2,
            5, 0, 3
        };

       if (!texturepaths.empty()) {
            std::vector<Texture> textures;
            for (int i = 0; i < texturepaths.size(); i++) {
                Texture tmp(texturepaths[i], types[i]);
                tmp.Load();
                textures.push_back(tmp);
            }
            meshes.push_back(Mesh(Vertex::genListVertex(vertices, numberVertices), Vertex::genListIndex(indices, numberIndices), textures));
        }      
        else {
            meshes.push_back(Mesh(Vertex::genListVertex(vertices, numberVertices), Vertex::genListIndex(indices, numberIndices), material));
        }
       meshes.back().DisableLocalMaterial();
	}
};
#endif