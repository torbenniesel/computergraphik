#pragma once

#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/VertexBufferLayout.h"

// OpenGL vertex array, used in class Mesh
class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	void Cleanup();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

