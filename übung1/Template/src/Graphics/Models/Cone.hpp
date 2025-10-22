#ifndef CONE_HPP
#define CONE_HPP

#include "Graphics/Model/Model.h"
#include "Graphics/Material/Material.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

class Cone : public Model {
public:
    bool noMat;
    std::vector<std::string> texturepaths;
    std::vector<aiTextureType> types;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> cost, sint;

    /// <summary>
    /// Draw a cone.
    /// </summary>
    /// <param name="base">Radius at the bottom of the cone</param>
    /// <param name="height">Z height</param>
    /// <param name="slices">The desired number of slices around the cone</param>
    /// <param name="stacks">The number of divisions along the z axis</param>
    /// <param name="color">Color of the cone, default = Color::blue</param>
    /// <remarks>The base of the cone is placed at Z = 0, and the top at Z = height. The cone is subdivided around the Z axis into slices, and along the Z axis into stacks. </remarks>
    Cone(
        float base = 1.0f, 
        float height = 1.0f, 
        int slices = 20, 
        int stacks = 3, 
        aiColor4D color = Color::blue
    ) 
        : Model (
            glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), true
        ), 
        texturepaths(), 
        types(), 
        noMat(false)
    {
        material.ambient = glm::vec4(color.r, color.g, color.b, color.a);
        material.diffuse = glm::vec4(color.r, color.g, color.b, color.a);
        material.specular = glm::vec4(color.r, color.g, color.b, color.a);
        material.shininess = 0.5f;

        init(base, height, slices, stacks);
    }

    /// <summary>
    /// Draw a cone.
    /// </summary>
    /// <param name="base">Radius at the bottom of the cone</param>
    /// <param name="height">Z height</param>
    /// <param name="slices">The desired number of slices around the cone</param>
    /// <param name="stacks">The number of divisions along the z axis</param>
    /// <param name="color">Color of the cone</param>
    /// <param name="pos">Sets a translation for the center of the cone</param>
    /// <param name="size">Sets the edgelenth for each dimension of the cone</param>
    /// <param name="rotation">Sets the rotation of the cone around its center</param>
    /// <remarks>The base of the cone is placed at Z = 0, and the top at Z = height. The cone is subdivided around the Z axis into slices, and along the Z axis into stacks. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Cone(
        float base, 
        float height, 
        int slices, 
        int stacks, 
        aiColor4D color, 
        glm::vec3 pos, 
        glm::vec3 size, 
        glm::vec3 rotation
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
        init(base, height, slices, stacks);
    }

    /// <summary>
    /// Draw a cone.
    /// </summary>
    /// <param name="base">Radius at the bottom of the cone</param>
    /// <param name="height">Z height</param>
    /// <param name="slices">The desired number of slices around the cone</param>
    /// <param name="stacks">The number of divisions along the z axis</param>
    /// <param name="_material">Material-Definition of the cone, default = Material::white_plastic</param>
    /// <remarks>The base of the cone is placed at Z = 0, and the top at Z = height. The cone is subdivided around the Z axis into slices, and along the Z axis into stacks.</remarks>
    Cone(
        float base, 
        float height, 
        int slices, 
        int stacks, 
        Material _material
    ) 
        : Model(
            glm::vec3(0.0f), 
            glm::vec3(1.0f), 
            glm::vec3(0.0f), 
            true
        ), 
        texturepaths(), 
        types(), 
        noMat(false)
    {
        material = _material;
        init(base, height, slices, stacks);
    }

    /// <summary>
    /// Draw a cone.
    /// </summary>
    /// <param name="base">Radius at the bottom of the cone</param>
    /// <param name="height">Z height</param>
    /// <param name="slices">The desired number of slices around the cone</param>
    /// <param name="stacks">The number of divisions along the z axis</param>
    /// <param name="_material">Material-Definition of the cone, default = Material::white_plastic</param>
    /// <param name="pos">Sets a translation for the center of the cone</param>
    /// <param name="size">Sets the edgelenth for each dimension of the cone</param>
    /// <param name="rotation">Sets the rotation of the cone around its center</param>
    /// <remarks>The base of the cone is placed at Z = 0, and the top at Z = height. The cone is subdivided around the Z axis into slices, and along the Z axis into stacks. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Cone(
        float base, 
        float height, 
        int slices, 
        int stacks, 
        Material _material, 
        glm::vec3 pos, 
        glm::vec3 size, 
        glm::vec3 rotation
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
        init(base, height, slices, stacks);
    }

    /// <summary>
    /// Draw a cone.
    /// </summary>
    /// <param name="base">Radius at the bottom of the cone</param>
    /// <param name="height">Z height</param>
    /// <param name="slices">The desired number of slices around the cone</param>
    /// <param name="stacks">The number of divisions along the z axis</param>
    /// <param name="texturepaths">List of filepaths for images used as textures</param>
    /// <param name="types">List of assoziated texture-types</param>
    /// <param name="pos">Sets a translation for the center of the cone</param>
    /// <param name="size">Sets the edgelenth for each dimension of the cone</param>
    /// <param name="rotation">Sets the rotation of the cone around its center</param>
    /// <remarks>The base of the cone is placed at Z = 0, and the top at Z = height. The cone is subdivided around the Z axis into slices, and along the Z axis into stacks. The specified transformations are applied to the model matrix directly before the draw-call</remarks>
    Cone(
        float base, 
        float height, 
        int slices, 
        int stacks, 
        std::vector<std::string> texturepaths, 
        std::vector<aiTextureType> types, 
        glm::vec3 pos = glm::vec3(0.0f), 
        glm::vec3 size = glm::vec3(1.0f), 
        glm::vec3 rotation = glm::vec3(0.0f)
    ) 
        : Model (
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
        init(base, height, slices, stacks); 
    }

    void init(float base, float height, int slices, int stacks) {
        fghGenerateCone((GLfloat)base, (GLfloat)height, slices, stacks);

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

    void fghGenerateCone(
        GLfloat base, GLfloat height, GLint slices, GLint stacks   /*  input */
    )
    {
        int i, j;
        int idx = 0;    /* idx into vertex/normal buffer */

        /* Step in z and radius as stacks are drawn. */
        GLfloat z = 0;
        GLfloat r = (GLfloat)base;

        const GLfloat zStep = (GLfloat)height / ((stacks > 0) ? stacks : 1);
        const GLfloat rStep = (GLfloat)base / ((stacks > 0) ? stacks : 1);

        /* Scaling factors for vertex normals */
        const GLfloat cosn = (GLfloat)(height / sqrt(height * height + base * base));
        const GLfloat sinn = (GLfloat)(base / sqrt(height * height + base * base));

        /* number of unique vertices */
        if (slices == 0 || stacks < 1)
        {
            /* nothing to generate */
            return;
        }
        int size = slices * (stacks + 2) + 1;
        /* need an extra stack for closing off bottom with correct normals */

        /* Pre-computed circle */
        fghCircleTable(-slices, GL_FALSE);

        /* bottom */
        vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, z), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f)));
        /* other on bottom (get normals right) */
        for (j = 0; j < slices; j++)
        {
            vertices.push_back(Vertex(glm::vec3(cost[j] * r, sint[j] * r, z), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f)));
        }

        /* each stack */
        for (i = 0; i < stacks + 1; i++)
        {
            for (j = 0; j < slices; j++)
            {
                vertices.push_back(Vertex(glm::vec3(cost[j] * r, sint[j] * r, z), glm::vec3(cost[j] * cosn, sint[j] * cosn, sinn), glm::vec3(0.0f)));
            }
            z += zStep;
            r -= rStep;
        }

        int centerIndex = 0;

        for (i = 0; i < slices; i++) {
            indices.push_back(centerIndex);
            //indices.push_back(i + 2);
            indices.push_back(((i + 1) % slices) + 1);
            indices.push_back(i + 1);
        }

        /* each stack */
        for (i = 0; i < stacks; i++)
        {
            int offset = 1 + (i + 1) * slices;
            for (j = 0; j < slices; j++)
            {
                indices.push_back(offset + j);
                indices.push_back(offset + ((j + 1) % slices));
                indices.push_back(offset + j + slices);

                indices.push_back(offset + ((j + 1) % slices));
                indices.push_back(offset + ((j + 1) % slices) + slices);
                indices.push_back(offset + j + slices);
            }
        }
    }

    void fghCircleTable(const int n, const GLboolean halfCircle)
    {
        int i;

        /* Table size, the sign of n flips the circle direction */
        const int size = abs(n);

        /* Determine the angle between samples */
        const GLfloat angle = (halfCircle ? 1 : 2) * (GLfloat)M_PI / (GLfloat)((n == 0) ? 1 : n);

        /* Allocate memory for n samples, plus duplicate of first entry at the end */
        sint.resize((size_t)size + (size_t)1);
        cost.resize((size_t)size + (size_t)1);

        /* Compute cos and sin around the circle */
        sint[0] = 0.0f;
        cost[0] = 1.0f;

        for (i = 1; i < size; i++)
        {
            sint[i] = (GLfloat)sin(angle * i);
            cost[i] = (GLfloat)cos(angle * i);
        }

        if (halfCircle)
        {
            sint[size] = 0.0f;  /* sin PI */
            cost[size] = -1.0f;  /* cos PI */
        }
        else
        {
            /* Last sample is duplicate of the first (sin or cos of 2 PI) */
            sint[size] = sint[0];
            cost[size] = cost[0];
        }
    }
};
#endif