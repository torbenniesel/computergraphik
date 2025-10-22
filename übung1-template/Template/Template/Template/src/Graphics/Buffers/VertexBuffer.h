#pragma once

// OpenGL Vertex Buffer, used in class Mesh
class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	void Cleanup();

	void Bind() const;
	void Unbind() const;
	void NewData(const void* data, unsigned int size);
};

