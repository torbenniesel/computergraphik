#pragma once

// IndexBuffer is used by class Mesh 
class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	void Cleanup();

	void Bind() const;
	void Unbind() const;
	void NewData(const unsigned int* data, unsigned int count);

	inline unsigned int GetCount() const { return m_Count; }
};
