#include "OrbitalCamera.h"
#include "Controllers/Devices/Mouse.h"
#include "Window/Window.h"

#include "glm/gtx/string_cast.hpp"
#include <chrono>

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

//void OrbitalCamera::Recalculate()
//{
//	// TODO U01.2: transform the spherical coordinates to cartesian 
//	//
//	// given: alpha, phi, distance, center (first in origin)
//	// wanted: position, front, right, up in [x,y,z] space
//	// 
//	// see excersise sheet
//	float radAlpha = glm::radians(alpha);
//	float radPhi = glm::radians(phi);
//	float camPosY = glm::sin(radPhi) * distance;
//	float radiusAtY = glm::cos(radPhi);
//	float camPosX = glm::cos(radAlpha) * radiusAtY * distance;
//	float camPosZ = glm::sin(radAlpha) * radiusAtY * distance;
//	position = center + glm::vec3(camPosX, camPosY, camPosZ);
//
//	glm::vec3 vecFront = center - position;
//
//	glm::vec3 referenceUp;
//	if (glm::abs(phi) > 89.0f) {
//		// Near poles: use forward direction to determine up
//		// Use a vector perpendicular to the view direction
//		referenceUp = glm::vec3(-glm::sin(radAlpha), 0.0f, glm::cos(radAlpha));
//	}
//	else {
//		// Normal case: use world up
//		referenceUp = glm::vec3(0.0f, 1.0f, 0.0f);
//	}
//
//	glm::vec3 vecSide = glm::cross(vecFront, referenceUp);
//	glm::vec3 vecUp = glm::cross(vecSide, vecFront);
//	up = glm::normalize(vecUp);
//
//	// debug output
//	printf("alpha %4.2f (%4.2f) phi: %4.2f ((%4.2f) pos: %4.2f %4.2f %4.2f front: %4.2f %4.2f %4.2f right: %4.2f %4.2f %4.2f up: %4.2f %4.2f %4.2f center: %4.2f %4.2f %4.2f\n",
//		alpha, radAlpha, phi, radPhi, position.x, position.y, position.z, front.x, front.y, front.z, right.x, right.y, right.z, up.x, up.y, up.z, center.x, center.y, center.z);
//}

void OrbitalCamera::Recalculate()
{
	// Transform spherical coordinates to Cartesian
	float radAlpha = glm::radians(alpha);
	float radPhi = glm::radians(phi);
	float camPosY = glm::sin(radPhi) * distance;
	float radiusAtY = glm::cos(radPhi);
	float camPosX = glm::cos(radAlpha) * radiusAtY * distance;
	float camPosZ = glm::sin(radAlpha) * radiusAtY * distance;
	position = center + glm::vec3(camPosX, camPosY, camPosZ);

	glm::vec3 vecFront = center - position;

	glm::vec3 referenceUp;
	if (glm::abs(phi) > 89.0f) {
		// Near poles: use forward direction to determine up
		// Use a vector perpendicular to the view direction
		referenceUp = glm::vec3(-glm::sin(radAlpha), 0.0f, glm::cos(radAlpha));
	}
	else {
		// Normal case: use world up
		referenceUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::vec3 vecSide = glm::cross(vecFront, referenceUp);
	glm::vec3 vecUp = glm::cross(vecSide, vecFront);

	// FIX: Normalize and store ALL basis vectors
	front = glm::normalize(vecFront);
	right = glm::normalize(vecSide);
	up = glm::normalize(vecUp);

	// debug output
	printf("alpha %4.2f (%4.2f) phi: %4.2f (%4.2f) pos: %4.2f %4.2f %4.2f front: %4.2f %4.2f %4.2f right: %4.2f %4.2f %4.2f up: %4.2f %4.2f %4.2f center: %4.2f %4.2f %4.2f\n",
		alpha, radAlpha, phi, radPhi, position.x, position.y, position.z, front.x, front.y, front.z, right.x, right.y, right.z, up.x, up.y, up.z, center.x, center.y, center.z);
}

void OrbitalCamera::Move(Direction dir, double deltaTime)
{
	// TODO U01.1: movement of the orbital camera
	// - calculate velocity from deltaTime [ms] and sensitivity [units/ms]
	// - calculate angle increment from velocity, the larger the distance the smaller the angle velocity

	float velocity = 10;
	float angular_velocity = 45;


	// move the camera position
	//change alpha (left, right),  phi (up, down), distance (forward, backward)
	switch (dir)
	{
	case Direction::NONE:
		break;
	case Direction::FORWARD:
		distance -= velocity * deltaTime;
		break;
	case Direction::BACKWARD:
		distance += velocity * deltaTime;
		break;
	case Direction::LEFT:
		alpha += angular_velocity * deltaTime;
		break;
	case Direction::RIGHT:
		alpha -= angular_velocity * deltaTime;
		break;
	case Direction::UP:
		phi += angular_velocity * deltaTime;
		// TODO U01.2: limit phi to ]-90,90[

		// TODO U01.3: remove the limit and modify Recalculate()

		// ...;
		break;
	case Direction::DOWN:
		phi -= angular_velocity * deltaTime;
		// TODO U01.2: limit phi to ]-90,90[

		// TODO U01.3: remove the limit and modify Recalculate()

		// ...;
		break;
	default:
		break;
	}

	// re-calculate pos, center, up from alpha, phi and distance
	Recalculate();

	// update view matrix, projection remains the same
	UpdateView();
}

void OrbitalCamera::MoveCenter(Direction dir, double deltaTime)
{
	// TODO U01.4: move the reference point of the orbital camera
	// see the procedure in move()



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