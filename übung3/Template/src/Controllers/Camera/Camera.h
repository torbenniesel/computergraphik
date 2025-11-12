#pragma once
#ifndef Camera_H
#define Camera_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Graphics/Shader/Shader.h"

//abstact class for a camera
class Camera
{
private:
	// view and projection matrices
	glm::mat4 viewMatrix, projectionMatrix;

protected:
	// default OpenGL camera parameters

	// camera
	glm::vec3 position;
	glm::vec3 center;
	glm::vec3 up;

	// symmetrical perspective view frustum 
	float aspect;
	float fovy;
	float near;
	float far;

public:
	// default camera looking from (15,15,15) to (0,0,0), 
	// fovy = 22.5, near = 1, far = 1000, aspect 16:9
	Camera();
	~Camera();

	// call update view- and projection matrix or both
	void UpdateView();
	void UpdateProjection();
	void Update();

	// view is based on position, center and up vectors
	inline void SetPosition(glm::vec3 p) { position = p; }
	inline void SetCenter(glm::vec3 c) { center = c; }
	inline void SetUp(glm::vec3 u) { up = u; }

	// projection is based on fovy, aspect, near and far	
	inline void SetFovy(float f) { // f in degrees
		if (f > 0 && f < 90.0f)
			fovy = glm::radians(f); 
	}  

	// add a method to modify fovy relative to its current value
	inline void AddFovy(float f) { 	// f in degrees
		// limit the zoom range to proper range
		fovy += glm::radians(f); 
		if (fovy < 0.001f) fovy = 0.001f;
		if (fovy > glm::pi<float>() / 2.0f) fovy = glm::pi<float>() / 2.0f;
	}  

	inline void SetAspect(float a) { aspect = a; }
	inline void SetNear(float n) { near = n; }
	inline void SetFar(float f) { far = f; }

	// set view / projection matrix
	inline void SetView(glm::mat4 view) { viewMatrix = view; }
	inline void SetProj(glm::mat4 proj) { projectionMatrix = proj; }

	// get camera parameters
	inline glm::vec3 GetPosition() { return position; };
	inline glm::vec3 GetCenter() { return center; };
	inline glm::vec3 GetUp() { return up; };

	// set projection parameters
	inline float SetFovy() { return fovy; }
	inline float SetAspect() { return aspect; }
	inline float SetNear() { return near; }
	inline float SetFar() { return far; }

	// get matrices 
	inline glm::mat4 GetViewMatrix() { return this->viewMatrix; };
	inline glm::mat4 GetProjectionMatrix() { return this->projectionMatrix; };

	// copy camera paramters to shader uniforms
	void Render(Shader shader);
};
#endif

