#include "Graphics/MatrixStack/MatrixStack.h"

// Matrixstack implementation
MatrixStack::MatrixStack() :
	matrixStack(0)
{
	currentMatrix = glm::mat4(1.0f);
}

void MatrixStack::PushMatrix()
{
	matrixStack.push_back(currentMatrix);
}

void MatrixStack::PopMatrix()
{
	currentMatrix = matrixStack.back();
	matrixStack.pop_back();
}

void MatrixStack::Clear()
{
	matrixStack.clear();
	currentMatrix = glm::mat4(1.0f);
}

void MatrixStack::Translate(glm::vec3 translate)
{
	currentMatrix = glm::translate(currentMatrix, translate);
}

void MatrixStack::Translate(float x, float y, float z)
{
	Translate(glm::vec3(x, y, z));
}

void MatrixStack::Scale(glm::vec3 scale)
{
	currentMatrix = glm::scale(currentMatrix, scale);
}

void MatrixStack::Scale(float x, float y, float z)
{
	Scale(glm::vec3(x, y, z));
}

void MatrixStack::Rotate(glm::vec3 rotate)
{
	if (rotate.x != 0) {
		currentMatrix = glm::rotate(currentMatrix, glm::radians(rotate.x), glm::vec3(1, 0, 0));
	}
	if (rotate.y != 0) {
		currentMatrix = glm::rotate(currentMatrix, glm::radians(rotate.y), glm::vec3(0, 1, 0));
	}
	if (rotate.z != 0) {
		currentMatrix = glm::rotate(currentMatrix, glm::radians(rotate.z), glm::vec3(0, 0, 1));
	}
}

void MatrixStack::Rotate(float x, float y, float z)
{
	Rotate(glm::vec3(x, y, z));
}

glm::mat4 MatrixStack::GetMatrix()
{
	return currentMatrix;
}
