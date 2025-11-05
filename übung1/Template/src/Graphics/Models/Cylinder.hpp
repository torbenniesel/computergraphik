#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif 

class Cylinder : public Model {
public:
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    /// <summary>
    /// Draw a cylinder.
    /// </summary>
    /// <param name="base">Radius of the cylinder</param>
    /// <param name="height">Height along the y-axis</param>
    /// <param name="slices">The desired number of slices around the cylinder</param>
    /// <param name="color">Color of the cylinder, default = Color::blue </param>
    /// <remarks> The constructor generates a cylinder centered at the origin, the center of whose base is at -height/2, whose top is at height/2 and whose axis is along the y axis. </remarks>
    Cylinder(float base = 1.0f, float height = 1.0f, unsigned int slices = 20, aiColor4D color = Color::blue) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types()
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init(base, height / 2.0f, slices);

    }

    /// <summary>
    /// Draw a cylinder.
    /// </summary>
    /// <param name="radius">Radius of the cylinder</param>
    /// <param name="height">Height along the y-axis</param>
    /// <param name="slices">The desired number of slices around the cylinder</param>
    /// <param name="color">Color of the cylinder</param>
    /// <param name="pos">Sets a translation for the center of the cylinder</param>
    /// <param name="size">Sets the extend for each dimension of the cylinder</param>
    /// <param name="rotation">Sets the rotation of the cylinder around its center</param>
    /// <remarks> The constructor generates a cylinder centered at the origin with y-height = 2 * halfextend. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
    Cylinder(float radius, float height, int slices, aiColor4D color, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types()
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init(radius, height / 2.0f, slices);
    }

    
    /// <summary>
    /// Draw a cylinder.
    /// </summary>
    /// <param name="radius">Radius of the cylinder</param>
    /// <param name="height">Height along the y-axis</param>
    /// <param name="slices">The desired number of slices around the cylinder</param>
    /// <param name="_material">Material-Definition of the cylinder</param>
    /// <remarks> The constructor generates a cylinder centered at the origin with y-height = 2 * halfextend. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
    Cylinder(float radius, float height, int slices, Material _material) : Model(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true), texturepaths(), types()
    {
        material = _material;
        init(radius, height / 2.0f, slices); 
    }

    /// <summary>
    /// Draw a cylinder.
    /// </summary>
    /// <param name="radius">Radius of the cylinder</param>
    /// <param name="height">Height along the y-axis</param>
    /// <param name="slices">The desired number of slices around the cylinder</param>
    /// <param name="_material">Material-Definition of the cylinder</param>
    /// <param name="pos">Sets a translation for the center of the cylinder</param>
    /// <param name="size">Sets the extend for each dimension of the cylinder</param>
    /// <param name="rotation">Sets the rotation of the cylinder around its center</param>
    /// <remarks> The constructor generates a cylinder centered at the origin with y-height = 2 * halfextend. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
    Cylinder(float radius, float height, int slices, Material _material, glm::vec3 pos, glm::vec3 size, glm::vec3 rotation) : Model(pos, size, rotation, true), texturepaths(), types()
    {
        material = _material;
        init(radius, height / 2.0f, slices);
    }

    /// <summary>
    /// Draw a cylinder.
    /// </summary>
    /// <param name="radius">Radius of the cylinder</param>
    /// <param name="height">Height along the y-axis</param>
    /// <param name="slices">The desired number of slices around the cylinder</param>
    /// <param name="texturepaths">List of filepaths for images used as textures</param>
    /// <param name="types">List of assoziated texture-types</param>
    /// <param name="pos">Sets a translation for the center of the cylinder</param>
    /// <param name="size">Sets the extend for each dimension of the cylinder</param>
    /// <param name="rotation">Sets the rotation of the cylinder around its center</param>
    /// <remarks> The constructor generates a cylinder centered at the origin with y-height = 2 * halfextend. The specified transformations are applied to the model matrix directly before the draw-call </remarks>
    Cylinder(float radius, float height, int slices, std::vector<std::string> texturepaths, std::vector<aiTextureType> types, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : Model(pos, size, rotation, false), texturepaths(texturepaths), types(types)
    {
        material = Material::white_plastic;
        init(radius, height / 2.0f, slices);
    }

    void init(float radius, float halfExtend, int slices) {
        fghGenerateCylinder(radius, halfExtend, slices);

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

    void fghGenerateCylinder(
        float radius, float halfExtend, unsigned int slices  /*  input */
    )
    {
        if (slices < 3) {
            slices = 3;
        }

        unsigned int i, j;

        unsigned int numberVertices = (slices + 2) * 2 + (slices + 1) * 2;
        unsigned int numberIndices = slices * 3 * 2 + slices * 6;

        float angleStep = (float)((2.0f * M_PI) / ((float)slices));

        vertices.push_back(Vertex(glm::vec3(0.0f, -halfExtend, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));

        for (i = 0; i < slices + 1; i++)
        {
            float currentAngle = angleStep * i;

            vertices.push_back(Vertex(glm::vec3(cosf(currentAngle) * radius, -halfExtend, -sinf(currentAngle) * radius), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f,0.0f)));
        }

        vertices.push_back(Vertex(glm::vec3(0.0f, halfExtend, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));

        for (i = 0; i < slices + 1; i++)
        {
            float currentAngle = angleStep * i;

            vertices.push_back(Vertex(glm::vec3(cosf(currentAngle) * radius, halfExtend, -sinf(currentAngle) * radius), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
        }

        for (i = 0; i < slices + 1; i++)
        {
            float currentAngle = angleStep * i;

            double sign = -1.0f;

            for (j = 0; j < 2; j++)
            {
                vertices.push_back(Vertex(glm::vec3(cosf(currentAngle) * radius, halfExtend * sign, -sinf(currentAngle) * radius), glm::vec3(cosf(currentAngle), 0.0f, -sinf(currentAngle)), glm::vec2((double)i / (double)slices, (sign + 1.0f) / 2.0f)));

                sign = 1.0f;
            }
        }

        unsigned int centerIndex = 0;
        unsigned int indexCounter = 1;
        for (i = 0; i < slices; i++)
        {
            indices.push_back(centerIndex);
            indices.push_back(indexCounter + 1);
            indices.push_back(indexCounter);

            indexCounter++;
        }

        indexCounter++;

        // Top
        centerIndex = indexCounter;
        indexCounter++;

        for (i = 0; i < slices; i++)
        {
            indices.push_back(centerIndex);
            indices.push_back(indexCounter);
            indices.push_back(indexCounter + 1);

            indexCounter++;
        }
        indexCounter++;

        // Sides
        for (i = 0; i < slices; i++)
        {
            indices.push_back(indexCounter);
            indices.push_back(indexCounter + 2);
            indices.push_back(indexCounter + 1);

            indices.push_back(indexCounter + 2);
            indices.push_back(indexCounter + 3);
            indices.push_back(indexCounter + 1);

            indexCounter += 2;
        }
    }
};
#endif