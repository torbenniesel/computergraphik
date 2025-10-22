#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include <string>

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

class Tetrahedron : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    /// <summary>
    /// Draw a tetrahedron (4-sided regular solid).
    /// </summary>
    /// <param name="color">Color of the tetrahedron, default = Color::blue</param>
    /// <remarks> centered at the modeling coordinates origin with a radius of \sqrt{3} </remarks>
    Tetrahedron(aiColor4D color = Color::blue) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Draw a tetrahedron (4-sided regular solid). 
    /// </summary>
    /// <param name="color">Color of the tetrahedron</param>
    /// <param name="pos">Sets a translation for the center of the tetrahedron</param>
    /// <param name="size">Sets the extend for each dimension of the tetrahedron</param>
    /// <param name="rotation">Sets the rotation of the tetrahedron around its center</param>
    /// <remarks> centered at the modeling coordinates origin with a radius of \sqrt{3}. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Tetrahedron(aiColor4D color, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(true)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Draw a tetrahedron (4-sided regular solid).
    /// </summary>
    /// <param name="_material">Material-Definition of the tetrahedron</param>
    /// <remarks> centered at the modeling coordinates origin with a radius of \sqrt{3}.</remarks>
    Tetrahedron(Material _material) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }

    /// <summary>
    /// Draw a tetrahedron (4-sided regular solid).
    /// </summary>
    /// <param name="pos">Sets a translation for the center of the tetrahedron</param>
    /// <param name="size">Sets the extend for each dimension of the tetrahedron</param>
    /// <param name="rotation">Sets the rotation of the tetrahedron around its center</param>
    /// <param name="_material">Material-Definition of the tetrahedron</param>
    /// <remarks> centered at the modeling coordinates origin with a radius of \sqrt{3}. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Tetrahedron(Material _material, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }
    

    /// <summary>
    /// Draw a tetrahedron (4-sided regular solid).
    /// </summary>
    /// <param name="texturepaths">List of filepaths for images used as textures</param>
    /// <param name="types">List of assoziated texture-types</param>
    /// <param name="pos">Sets a translation for the center of the tetrahedron</param>
    /// <param name="size">Sets the extend for each dimension of the tetrahedron</param>
    /// <param name="rotation">Sets the rotation of the tetrahedron around its center</param>
    /// <remarks> centered at the modeling coordinates origin with a radius of \sqrt{3}. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Tetrahedron(std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types), noMat(false) 
    { 
        material = Material::white_plastic;
        init(); 
    }

    

    

	void init() {
        int numberVertices = 4;
        float vertices[] = {
            // position                                             normal                              texcoord
            -1.732050807568f, -1.732050807568f,  1.732050807568f,   -0.57735f, -0.57735f,  0.57735f,    0.0f, 0.0f,
             1.732050807568f,  1.732050807568f,  1.732050807568f,    0.57735f,  0.57735f,  0.57735f,    0.0f, 0.0f,
            -1.732050807568f,  1.732050807568f, -1.732050807568f,   -0.57735f,  0.57735f, -0.57735f,    0.0f, 0.0f,
             1.732050807568f, -1.732050807568f, -1.732050807568f,    0.57735f, -0.57735f, -0.57735f,    0.0f, 0.0f
        };
        
        int numberIndices = 12;
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
            2, 1, 3,
            3, 1, 0
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