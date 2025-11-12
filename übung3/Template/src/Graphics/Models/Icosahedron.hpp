#ifndef ICOSAHEDRON_HPP
#define ICOSAHEDRON_HPP

#include <string>

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

class Icosahedron : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    /// <summary>
    /// Draw a icosahedron (20-sided regular solid).
    /// </summary>
    /// <param name="color">Color of the icosahedron, default = Color::blue</param>
    /// <remarks> The icosahedron is centered at the modeling coordinates origin and has a radius of 1.0. </remarks>
    Icosahedron(aiColor4D color = Color::blue) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Draw a icosahedron (20-sided regular solid). 
    /// </summary>
    /// <param name="color">Color of the icosahedron</param>
    /// <param name="pos">Sets a translation for the center of the icosahedron</param>
    /// <param name="size">Sets the extend for each dimension of the icosahedron</param>
    /// <param name="rotation">Sets the rotation of the tetrahedron around its center</param>
    /// <remarks> The icosahedron is centered at the modeling coordinates origin and has a radius of 1.0. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Icosahedron(aiColor4D color, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(true)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Draw a icosahedron (20-sided regular solid).
    /// </summary>
    /// <param name="_material">Material-Definition of the icosahedron</param>
    /// <remarks> The icosahedron is centered at the modeling coordinates origin and has a radius of 1.0.</remarks>
    Icosahedron(Material _material) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }

    /// <summary>
    /// Draw a icosahedron (20-sided regular solid).
    /// </summary>
    /// <param name="pos">Sets a translation for the center of the icosahedron</param>
    /// <param name="size">Sets the extend for each dimension of the icosahedron</param>
    /// <param name="rotation">Sets the rotation of the tetrahedron around its center</param>
    /// <param name="_material">Material-Definition of the icosahedron</param>
    /// <remarks> The icosahedron is centered at the modeling coordinates origin and has a radius of 1.0. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Icosahedron(Material _material, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }
    

    /// <summary>
    /// Draw a icosahedron (20-sided regular solid).
    /// </summary>
    /// <param name="texturepaths">List of filepaths for images used as textures</param>
    /// <param name="types">List of assoziated texture-types</param>
    /// <param name="pos">Sets a translation for the center of the icosahedron</param>
    /// <param name="size">Sets the extend for each dimension of the icosahedron</param>
    /// <param name="rotation">Sets the rotation of the tetrahedron around its center</param>
    /// <remarks> The icosahedron is centered at the modeling coordinates origin and has a radius of 1.0. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Icosahedron(std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types), noMat(false)
    { 
        material = Material::white_plastic;
        init(); 
    }

    

    

	void init() {
        int numberVertices = 12;
        float vertices[] = {
            // position                            normal                                 texcoord
                  0.0f, -0.525731f, -0.850651f,          0.0f, -0.525731f, -0.850651f,    0.0f, 0.0f,
                  0.0f,  0.525731f, -0.850651f,          0.0f,  0.525731f, -0.850651f,    0.0f, 0.0f,
                  0.0f,  0.525731f,  0.850651f,          0.0f,  0.525731f,  0.850651f,    0.0f, 0.0f,
                  0.0f, -0.525731f,  0.850651f,          0.0f, -0.525731f,  0.850651f,    0.0f, 0.0f
            -0.525731f, -0.850651f,       0.0f,    -0.525731f, -0.850651f,       0.0f,    0.0f, 0.0f,
             0.525731f, -0.850651f,       0.0f,     0.525731f, -0.850651f,       0.0f,    0.0f, 0.0f,
             0.525731f,  0.850651f,       0.0f,     0.525731f,  0.850651f,       0.0f,    0.0f, 0.0f,
            -0.525731f,  0.850651f,       0.0f,    -0.525731f,  0.850651f,       0.0f,    0.0f, 0.0f,
            -0.850651f,       0.0f,  0.525731f,    -0.850651f,       0.0f,  0.525731f,    0.0f, 0.0f,
             0.850651f,       0.0f,  0.525731f,     0.850651f,       0.0f,  0.525731f,    0.0f, 0.0f,
            -0.850651f,       0.0f, -0.525731f,    -0.850651f,       0.0f, -0.525731f,    0.0f, 0.0f,
             0.850651f,       0.0f, -0.525731f,     0.850651f,       0.0f, -0.525731f,    0.0f, 0.0f
        };
        
        int numberIndices = 60;
        unsigned int indices[] = {
             2,  6,  7,
             7,  6,  1,
            11,  0,  1,
             0,  8,  1,
             4,  9,  8,
             8,  9,  7,
             9,  3,  2,
            10,  2,  3,
             5, 11, 10,
            11,  6, 10,
             0,  5,  4,
             5,  3,  4,
             6,  2, 10,
             6, 11,  1,
             1,  8,  7,
             9,  2,  7,
             3,  5, 10,
             0, 11,  5,
             3,  9,  4,
             0,  4,  8
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