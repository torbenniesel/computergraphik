#pragma once
#ifndef MODELSTACK_H
#define MODELSTACK_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MatrixStack
{
public:
	/// <summary>
	/// Constructor
	/// Current transform is unit matrix 
	/// </summary>
	MatrixStack();

	/// <summary>
	/// Save the current coordinate system (transform) with PushMatrix(), use PopMatrix() to restore
	/// </summary>
	/// 
	void PushMatrix();
	/// <summary>
	/// Save the current coordinate system (transform) with PushMatrix(), use PopMatrix() to restore
	/// </summary>
	void PopMatrix();

	/// <summary>
	/// Move the current coordinate system (transform)
	/// </summary>
	/// <param name="translate">3d translation vector</param>
	void Translate(glm::vec3 translate = glm::vec3(0.0f));

	/// <summary>
	/// Move the current coordinate system (transform)
	/// </summary>
	/// <param name="x">translation along X axis</param>
	/// <param name="y">translation along Y axis</param>
	/// <param name="z">translation along Z axis</param>
	void Translate(float x, float y, float z);

	/// <summary>
	/// Scale the current coordinate system (transform)
	/// </summary>
	/// <param name="scale">3d scaling factors</param>
	void Scale(glm::vec3 scale = glm::vec3(1.0f));

	/// <summary>
	/// Scale the current coordinate system (transform)
	/// </summary>
	/// <param name="x">scaling factor of X axis</param>
	/// <param name="y">scaling factor of Y axis</param>
	/// <param name="z">scaling factor of Z axis</param>
	void Scale(float x, float y, float z);

	/// <summary>
	/// Rotate the current coordinate system (transform) 
	/// Rotation order: 
	///     1. x degrees around X axis
	///     2. y degrees around Y axis
	///     3. z degrees around Z axis
	/// </summary>
	/// <param name="rotate">rotation angles</param>

	void Rotate(glm::vec3 rotate = glm::vec3(0.0f));
	/// <summary>
	/// Rotate the current coordinate system (transform) 
	/// Rotation order: 
	///     1. x degrees around X axis
	///     2. y degrees around Y axis
	///     3. z degrees around Z axis
	/// </summary>
	/// <param name="x">rotation angle around X axis, math. positive</param>
	/// <param name="y">rotation angle around Y axis, math. positive</param>
	/// <param name="z">rotation angle around Z axis, math. positive</param>
	void Rotate(float rx, float ry, float rz);

	/// <summary>
	///  Get the current coordinate system (transform)
	/// </summary>
	/// <returns></returns>
	glm::mat4 GetMatrix();

	/// <summary>
	/// Empty the matrix stack
	/// </summary>
	void Clear();

private:
	std::vector<glm::mat4> matrixStack;
	glm::mat4 currentMatrix;
};
#endif

