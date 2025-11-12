#include "OrbitalCamera.h"
#include "Controllers/Devices/Mouse.h"
#include "Window/Window.h"

#include "glm/gtx/string_cast.hpp"

OrbitalCamera::OrbitalCamera(float alpha, float phi, float distance) :
	alpha(alpha),
	phi(phi),
	distance(distance),
	front(0),
	right(0)
{
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	Recalculate();
	Update();
}

OrbitalCamera::~OrbitalCamera()
{
}

void OrbitalCamera::Recalculate()
{
	// calculation of position using a unit sphere (r == 1, center == origin)
	glm::vec3 p = glm::vec3(0);
	p.x = sin(glm::radians(alpha)) * cos(glm::radians(phi)); // sin, cos use radians !!
	p.y = sin(glm::radians(phi));
	p.z = cos(glm::radians(alpha)) * cos(glm::radians(phi));
	front = -p;  // opposite direction, no need to normalize since p is a unit vector

	if (90.0f < phi || -90.0f > phi) // "back side" if(phi > 90 || phi < -90)
		right = glm::normalize(glm::cross(earthYAxis, front));
	else							 // "front side" between 90 and -90
		right = glm::normalize(glm::cross(front, earthYAxis));

	up = glm::normalize(glm::cross(right, front));

	position = center + p * distance;
	// same as: position = center - distance * front;

	// debug output
	// printf("alpha %4.2f phi: %4.2f pos: %4.2f %4.2f %4.2f front: %4.2f %4.2f %4.2f right: %4.2f %4.2f %4.2f up: %4.2f %4.2f %4.2f center: %4.2f %4.2f %4.2f\n",
	//	alpha, phi, position.x, position.y, position.z, front.x, front.y, front.z, right.x, right.y, right.z, up.x, up.y, up.z, center.x, center.y, center.z);
}

void OrbitalCamera::Move(Direction dir, double deltaTime)
{
	// movement of the orbital camera
	// - calculate velocity from deltaTime [ms] and sensitivity [units/ms]
	// - calculate angle increment from velocity, the larger the distance the smaller the angle velocity

	float velocity = 0;
	float angular_velocity = 0;

	velocity = (float)deltaTime * sensitivity; // in units
	angular_velocity = 180.0f * velocity / (glm::pi<float>() * distance); // in degrees

	// move the camera position
	switch (dir)
	{
	case Direction::NONE:
		break;
	case Direction::FORWARD:
		distance -= velocity;
		if (distance < 1.5f * near) distance = 1.5f * near; // depends on scene
		break;
	case Direction::BACKWARD:
		distance += velocity;
		break;
	case Direction::LEFT:
		alpha -= angular_velocity;
		while (0 > alpha) alpha += 360.0f;
		break;
	case Direction::RIGHT:
		alpha += angular_velocity;
		while (360.0f <= alpha ) alpha -= 360.0f;
		break;
	case Direction::UP:
		phi += angular_velocity;
		while (180.0f <= phi)
			phi -= 360.0f;
		break;
	case Direction::DOWN:
		phi -= angular_velocity;
		while (-180.0f > phi)
			phi += 360.0f;
		break;
	default:
		break;
	}

	// re-calculate pos, center, up from alpha, phi and distance
	Recalculate();

	// update view matrix, projection remains the same
	UpdateView();
}

void OrbitalCamera::Move(glm::vec3 dir, double deltaTime) {

	float velocity = 0;
	velocity = (float)deltaTime * sensitivity; // in units

	alpha -= dir.x * velocity;
	phi -= dir.y * velocity;
	distance -= dir.z * velocity;

	while (360.0f <= alpha) alpha -= 360.0f;
	while (0 > alpha) alpha += 360.0f;
	while (180.0f <= phi) phi -= 360.0f;
	while (-180.0f > phi) phi += 360.0f;
	if (distance < 1.5f * near) distance = 1.5f * near;

	// re-calculate pos, center, up from alpha, phi and distance
	Recalculate();

	// update view matrix, projection remains the same
	UpdateView();
}

void OrbitalCamera::MoveCenter(Direction dir, double deltaTime)
{
	float velocity = (float)deltaTime * sensitivity;

	switch (dir)
	{
	case Direction::NONE:
		break;
	case Direction::FORWARD:
		center += velocity * front;
		break;
	case Direction::BACKWARD:
		center -= velocity * front;
		break;
	case Direction::LEFT:
		center -= velocity * right;
		break;
	case Direction::RIGHT:
		center += velocity * right;
		break;
	case Direction::UP:
		center += velocity * up;
		break;
	case Direction::DOWN:
		center -= velocity * up;
		break;
	default:
		break;
	}

	// re-calculate pos, center, up
	Recalculate();

	// update view matrix, projection remains the same
	UpdateView();
}

// TODO U03.2: implementation of the method to move the center using the mouse
// ...
void OrbitalCamera::MoveCenter(glm::vec3 dir, double deltaTime)
{
	float velocity = (float)deltaTime * sensitivity;

	center += velocity * -dir.x * right;
	center += velocity * -dir.y * up;
	center += velocity * dir.z * front;

	// re-calculate pos, center, up
	Recalculate();

	// update view matrix, projection remains the same
	UpdateView();
}


void OrbitalCamera::Reset()
{
	alpha = initialAlpha;
	phi = initialPhi;
	distance = initialDistance;

	// calculate pos, center, up
	Recalculate();
	// update view and projection matrix
	UpdateView();
}