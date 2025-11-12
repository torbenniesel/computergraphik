#ifndef DOME_HPP
#define DOME_HPP

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

class Dome : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Dome(std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f), float radius = 1, int slices = 20) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types), noMat(false) 
    { 
        material = Material::white_plastic;
        init(radius, slices); 
    }
    Dome(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f), Material _material = Material::white_plastic, float radius = 1, int slices = 20) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(false) 
    { 
        material = _material;
        init(radius, slices); 
    }
    Dome(aiColor4D color, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f), float radius = 1, int slices = 20) : Model(pos, size, rotation, true), texturepaths(), types(), noMat(true) 
    { 
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init(radius, slices); 
    }

    void init(float radius, int slices) {
        fghGenerateDome(radius, slices);

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

    void fghGenerateDome(
        float radius, unsigned int slices  /*  input */
    )
    {
        if (slices < 3) {
            slices = 3;
        }

        unsigned int i, j;

        unsigned int numberParallels = slices / 4;
        unsigned int numberVertices = (numberParallels + 1) * (slices + 1);
        unsigned int numberIndices = numberParallels * slices * 6;

        float angleStep = (float)(2.0f * M_PI) / ((float)slices);

        for (i = 0; i < numberParallels + 1; i++)
        {
            for (j = 0; j < slices + 1; j++)
            {
                glm::vec3 vertex_pos = glm::vec3(
                    radius * sinf(angleStep * i) * sinf(angleStep * j), 
                    radius * cosf(angleStep * i), 
                    radius * sinf(angleStep * i) * cosf(angleStep * j)
                );
                vertices.push_back(Vertex(vertex_pos, 
                    glm::vec3(vertex_pos / radius), 
                    glm::vec2(j / (float)slices, 1.0f - i / (float)numberParallels))
                );
            }
        }

        for (i = 0; i < numberParallels; i++)
        {
            for (j = 0; j < slices; j++)
            {
                indices.push_back(i * (slices + 1) + j);
                indices.push_back((i + 1) * (slices + 1) + j);
                indices.push_back((i + 1) * (slices + 1) + (j + 1));

                indices.push_back(i * (slices + 1) + j);
                indices.push_back((i + 1) * (slices + 1) + (j + 1));
                indices.push_back(i * (slices + 1) + (j + 1));
            }
        }
    }
};
#endif