#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Mesh/Mesh.h"

#include <iostream>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
}

void VertexArray::Cleanup() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		//std::cout << "Count: " << element.count << " Type: " << element.type << " Stride: " << layout.GetStride() << " Offset: " << offset << std::endl;
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}