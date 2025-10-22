#include "Graphics/Texture/Texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <iostream>

Texture::Texture()
{
    id = -1;
    type = aiTextureType_NONE;
}

Texture::Texture(std::string filepath, aiTextureType type) : 
    path(""), 
    filepath(filepath), 
    type(type)
{
    Generate();
}

Texture::Texture(std::string dir, std::string path, aiTextureType type) : 
    path(path), 
    filepath((dir + "/" + path)), 
    type(type)
{
    Generate();
}

void Texture::Generate()
{
	glGenTextures(1, &id);
}

void Texture::Load(bool flip)
{
    stbi_set_flip_vertically_on_load(flip);

    int width, height, nChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);

    GLenum colorMode = GL_RGB;
    switch (nChannels)
    {
    case 1:
        colorMode = GL_RED;
        break;
    case 4:
        colorMode = GL_RGBA;
        break;
    }

    if (data) {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
        std::cout << "Failed to load texture: " << filepath << std::endl;
    }

    stbi_image_free(data);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}
