#include "Graphics/Buffers/IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer() :m_Count(0) {
   glGenBuffers(1, &m_RendererID);
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_Count(count){
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Cleanup() {

    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::NewData(const unsigned int* data, unsigned int count) {
    m_Count = count;
    glDeleteBuffers(1, &m_RendererID);
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}