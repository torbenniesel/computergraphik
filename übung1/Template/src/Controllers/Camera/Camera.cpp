#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(15.0f, 15.0f, 30.0f);
	center = glm::vec3(0);
	up = glm::vec3(0, 1.0f, 0);
	aspect = 16.9f; 
	fovy = glm::radians(22.5f);
	near = 1.0f; far = 1000.0f;
	projectionMatrix = glm::perspective(2*fovy, aspect, near, far);
	viewMatrix = glm::lookAt(position, center, up);
}

Camera::~Camera()
{

}

void Camera::UpdateView()
{
	viewMatrix = glm::lookAt(position, center, up);
}

void Camera::UpdateProjection()
{
	projectionMatrix = glm::perspective(2*fovy, aspect, near, far);
}

void Camera::Update()
{
	UpdateView();
	UpdateProjection();
}

void Camera::Render(Shader shader)
{
	shader.Bind();
	shader.SetMat4("view", viewMatrix);
	shader.SetMat4("projection", projectionMatrix);
	shader.Set3Float("viewPos", position);
}
