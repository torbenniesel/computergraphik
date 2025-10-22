#pragma once
#include <vector>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// OpenGL vertex buffer layout, used by class Mesh

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		default:
			return 0;
		}
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() :m_Stride(0) {};

	template<typename T>
	struct empty : std::false_type
	{ };

	template<typename T>
	void Push(unsigned int count) {
		static_assert(false, "This function has to be implemented for the desired type!");
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	template<>
	void Push<glm::vec2>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count * 2, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count * 2;
	}

	template<>
	void Push<glm::vec3>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count * 3, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count * 3;
	}

	template<>
	void Push<glm::vec4>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count * 4, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count * 4;
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements;  }
	inline unsigned int GetStride() const { return m_Stride; }
};

