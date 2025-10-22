#ifndef TORUS_HPP
#define TORUS_HPP

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

class Torus : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Torus(
        std::vector<std::string> texturepaths, 
        std::vector<aiTextureType> types, 
        glm::vec3 pos = glm::vec3(0.0f), 
        glm::vec3 size = glm::vec3(1.0f), 
        glm::vec3 rotation = glm::vec3(0.0f), 
        float inner_radius = 1, 
        float outer_radius = 2, 
        int slices = 20, 
        int stacks = 5
    ) 
        : Model(
            pos, 
            size, 
            rotation, 
            false
        ), 
        texturepaths(texturepaths), 
        types(types), 
        noMat(false) 
    { 
        material = Material::white_plastic;
        init(inner_radius, outer_radius, slices, stacks); 
    }

    Torus(
        glm::vec3 pos = glm::vec3(0.0f), 
        glm::vec3 size = glm::vec3(1.0f), 
        glm::vec3 rotation = glm::vec3(0.0f), 
        Material _material = Material::white_plastic, 
        float inner_radius = 1, 
        float outer_radius = 2, 
        int slices = 20, 
        int stacks = 5
    ) 
        : Model(
            pos, 
            size, 
            rotation, 
            true
        ), 
        texturepaths(), 
        types(), 
        noMat(false) 
    { 
        material = _material;
        init(inner_radius, outer_radius, slices, stacks); 
    }

    Torus(
        aiColor4D color, 
        glm::vec3 pos = glm::vec3(0.0f), 
        glm::vec3 size = glm::vec3(1.0f), 
        glm::vec3 rotation = glm::vec3(0.0f), 
        float inner_radius = 1, 
        float outer_radius = 2, 
        int slices = 20, 
        int stacks = 5
    ) 
        : Model(
            pos, 
            size, 
            rotation, 
            true
        ), 
        texturepaths(), 
        types(), 
        noMat(true) 
    { 
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init(inner_radius, outer_radius, slices, stacks); 
    }

    void init(float inner_radius, float outer_radius, int slices, int stacks) {
        fghGenerateTorus(inner_radius, outer_radius, slices, stacks);

       
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

    void fghGenerateTorus(
        float inner_radius, float outer_radius, unsigned int slices, unsigned int stacks  /*  input */
    )
    {
        if (slices < 3) {
            slices = 3;
        }
        if (stacks < 3) {
            stacks = 3;
        }

        float s = 0;
        float t = 0;

        float sIncr;
        float tIncr;

        float cos2PIs, sin2PIs, cos2PIt, sin2PIt;

        // loop counters
        unsigned int sideCount, faceCount;

        // used to generate the indices
        unsigned int v0, v1, v2, v3;

        float torusRadius = (outer_radius - inner_radius) / 2.0f;
        float centerRadius = outer_radius - torusRadius;
        
        sIncr = 1.0f / (float)slices;
        tIncr = 1.0f / (float)stacks;

        for (sideCount = 0; sideCount <= slices; ++sideCount, s += sIncr)
        {
            cos2PIs = (float)cosf((float)(2.0f * M_PI * s));
            sin2PIs = (float)sinf((float)(2.0f * M_PI * s));

            t = 0.0f;

            for (faceCount = 0; faceCount <= stacks; ++faceCount, t += tIncr)
            {
                cos2PIt = (float)cosf((float)(2.0f * M_PI * t));
                sin2PIt = (float)sinf((float)(2.0f * M_PI * t));

                glm::vec3 vertex_pos = glm::vec3((centerRadius + torusRadius * cos2PIt) * cos2PIs, (centerRadius + torusRadius * cos2PIt) * sin2PIs, torusRadius * sin2PIt);
                vertices.push_back(Vertex(vertex_pos, glm::vec3(cos2PIs * cos2PIt, sin2PIs * cos2PIt, sin2PIt), glm::vec2(s,t)));
            }
        }

        for (sideCount = 0; sideCount < slices; ++sideCount)
        {
            for (faceCount = 0; faceCount < stacks; ++faceCount)
            {
                v0 = ((sideCount * (stacks + 1)) + faceCount);
                v1 = (((sideCount + 1) * (stacks + 1)) + faceCount);
                v2 = (((sideCount + 1) * (stacks + 1)) + (faceCount + 1));
                v3 = ((sideCount * (stacks + 1)) + (faceCount + 1));

                indices.push_back(v0);
                indices.push_back(v1);
                indices.push_back(v2);

                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v3);
            }
        }
    }
};
#endif