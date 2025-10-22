#ifndef DODECAHEDRON_HPP
#define DODECAHEDRON_HPP

#include <string>

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

class Dodecahedron : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    /// <summary>
    /// Create a dodecahedron (12-sided regular solid)
    /// </summary>
    /// <param name="color">Color of the dodecahedron, default = Color::blue</param>
    /// <remarks> The dodecahedron centered at the modeling coordinates origin with a radius of \sqrt{3}. </remarks>
    Dodecahedron(aiColor4D color = Color::blue) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Create a dodecahedron (12-sided regular solid)
    /// </summary>
    /// <param name="color">Color of the dodecahedron</param>
    /// <param name="pos">Sets a translation for the center of the dodecahedron</param>
    /// <param name="size">Sets the extend for each dimension of the dodecahedron</param>
    /// <param name="rotation">Sets the rotation of the dodecahedron around its center</param>
    /// <remarks> The dodecahedron centered at the modeling coordinates origin with a radius of \sqrt{3}. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
    Dodecahedron(aiColor4D color, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(true)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init();
    }

    /// <summary>
    /// Create a dodecahedron (12-sided regular solid)
    /// </summary>
    /// <param name="_material">Material-Definition of the dodecahedron</param>
    /// <remarks> The dodecahedron centered at the modeling coordinates origin with a radius of \sqrt{3}.</remarks>
    Dodecahedron(Material _material) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }

    /// <summary>
    /// Create a dodecahedron (12-sided regular solid)
    /// </summary>
    /// <param name="_material">Material-Definition of the dodecahedron</param>
    /// <param name="pos">Sets a translation for the center of the dodecahedron</param>
    /// <param name="size">Sets the extend for each dimension of the dodecahedron</param>
    /// <param name="rotation">Sets the rotation of the dodecahedron around its center</param>
    /// <remarks> The dodecahedron centered at the modeling coordinates origin with a radius of \sqrt{3}. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
    Dodecahedron(Material _material, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(false)
    {
        material = _material;
        init();
    }

    /// <summary>
    /// Create a dodecahedron (12-sided regular solid)
    /// </summary>
    /// <param name="texturepaths">List of filepaths for images used as textures</param>
    /// <param name="types">List of assoziated texture-types</param>
    /// <param name="pos">Sets a translation for the center of the dodecahedron</param>
    /// <param name="size">Sets the extend for each dimension of the dodecahedron</param>
    /// <param name="rotation">Sets the rotation of the dodecahedron around its center</param>
    /// <remarks> The dodecahedron centered at the modeling coordinates origin with a radius of \sqrt{3}. The specified transformations are applied to the model matrix directly before the draw-call.</remarks>
    Dodecahedron(std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types), noMat(false)
    { 
        material = Material::white_plastic;
        init(); 
    }

    

    

	void init() {
        float alpha = sqrt(2.0f / (3.0f + sqrt(5.0f))); //0.618034f
        float beta = 1.0f + sqrt(6.0f / (3.0f + sqrt(5.0f)) - 2.0f + 2.0f * sqrt(2.0f / (3.0f + sqrt(5.0f)))); // 1.61803f

        int numberVertices = 20;
        float vertices[] = {
            // position                           normal                              texcoord
                  1.0f,      1.0f,      1.0f,     0.57735f,  0.57735f,  0.57735f,     0.0f, 0.0f,
                  1.0f,      1.0f,     -1.0f,     0.57735f,  0.57735f, -0.57735f,     0.0f, 0.0f,
                  1.0f,     -1.0f,      1.0f,     0.57735f, -0.57735f,  0.57735f,     0.0f, 0.0f,
                  1.0f,     -1.0f,     -1.0f,     0.57735f, -0.57735f, -0.57735f,     0.0f, 0.0f,
                 -1.0f,      1.0f,      1.0f,    -0.57735f,  0.57735f,  0.57735f,     0.0f, 0.0f,
                 -1.0f,      1.0f,     -1.0f,    -0.57735f,  0.57735f, -0.57735f,     0.0f, 0.0f,
                 -1.0f,     -1.0f,      1.0f,    -0.57735f, -0.57735f,  0.57735f,     0.0f, 0.0f,
                 -1.0f,     -1.0f,     -1.0f,    -0.57735f, -0.57735f, -0.57735f,     0.0f, 0.0f,
                  0.0f,  0.61804f,  1.61803f,         0.0f,  0.35682f,  0.93417f,     0.0f, 0.0f,
                  0.0f,  0.61804f, -1.61803f,         0.0f,  0.35682f, -0.93417f,     0.0f, 0.0f,
                  0.0f, -0.61804f,  1.61803f,         0.0f, -0.35682f,  0.93417f,     0.0f, 0.0f,
                  0.0f, -0.61804f, -1.61803f,         0.0f, -0.35682f, -0.93417f,     0.0f, 0.0f,
              0.61804f,  1.61803f,      0.0f,     0.35682f,  0.93417f,      0.0f,     0.0f, 0.0f,
              0.61804f, -1.61803f,      0.0f,     0.35682f, -0.93417f,      0.0f,     0.0f, 0.0f,
             -0.61804f,  1.61803f,      0.0f,    -0.35682f,  0.93417f,      0.0f,     0.0f, 0.0f,
             -0.61804f, -1.61803f,      0.0f,    -0.35682f, -0.93417f,      0.0f,     0.0f, 0.0f,
              1.61803f,      0.0f,  0.61804f,     0.93417f,      0.0f,  0.35682f,     0.0f, 0.0f,
              1.61803f,      0.0f, -0.61804f,     0.93417f,      0.0f, -0.35682f,     0.0f, 0.0f,
             -1.61803f,      0.0f,  0.61804f,    -0.93417f,      0.0f,  0.35682f,     0.0f, 0.0f,
             -1.61803f,      0.0f, -0.61804f,    -0.93417f,      0.0f, -0.35682f,     0.0f, 0.0f
        };

        int numberIndices = 108;
        unsigned int indices[] = {
            19, 18,  4,
            11,  7, 19,
            13,  2, 10,
            16, 17,  1,
            10,  2, 16,
            13,  3, 17,
            15,  7, 11,
             6, 18, 19,
             6, 10,  8,
             0, 12, 14,
             1,  9,  5,
            17,  3, 11,
            14,  5,  4,
             5, 19,  4,
             5,  9, 19,
             9, 11, 19,
             6, 15, 10,
            15, 13, 10,
            12,  0,  1,
             0, 16,  1,
             0,  8, 16,
             8, 10, 16,
            16,  2, 17,
             2, 13, 17,
             3, 14, 11,
            13, 15, 11,
             7, 15, 19,
            15,  6, 19,
             4, 18,  8,
            18,  6,  8,
             4,  8, 14,
             8,  0, 14,
            14, 12,  5,
            12,  1,  5,
             9,  1, 11,
             1, 17, 11
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