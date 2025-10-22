#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include <assimp/scene.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentgSource;
};

// OpenGL shader class
class Shader {
private:
	std::string m_FilePath;
	ShaderProgramSource source;
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

	int GetUniformLocation(const std::string& name) const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
public:
	Shader(const std::string& filepath);
	void Cleanup();

	void Bind();
	void Unbind() const;

	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void Set3Float(const std::string& name, glm::vec3 value);
	void Set3Float(const std::string& name, float v1, float v2, float v3);
	void Set4Float(const std::string& name, float v0, float v1, float v2, float v3);
	void Set4Float(const std::string& name, aiColor4D color);
	void Set4Float(const std::string& name, glm::vec4 value);
	void SetMat4(const std::string& name, const glm::mat4 matrix);
};

