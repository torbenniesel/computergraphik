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
	// TODO U01.2: transform the spherical coordinates to cartesian 
	//
	// given: alpha, phi, distance, center (first in origin)
	// wanted: position, front, right, up in [x,y,z] space
	// 
	// see excersise sheet


	// debug output
	printf("alpha %4.2f phi: %4.2f pos: %4.2f %4.2f %4.2f front: %4.2f %4.2f %4.2f right: %4.2f %4.2f %4.2f up: %4.2f %4.2f %4.2f center: %4.2f %4.2f %4.2f\n",
		alpha, phi, position.x, position.y, position.z, front.x, front.y, front.z, right.x, right.y, right.z, up.x, up.y, up.z, center.x, center.y, center.z);
}

void OrbitalCamera::Move(Direction dir, double deltaTime)
{
	// TODO U01.1: movement of the orbital camera
	// - calculate velocity from deltaTime [ms] and sensitivity [units/ms]
	// - calculate angle increment from velocity, the larger the distance the smaller the angle velocity

	float velocity = 0;
	float angular_velocity = 0;


	// move the camera position
	switch (dir)
	{
	case Direction::NONE:
		break;
	case Direction::FORWARD:
		//...		
		break;
	case Direction::BACKWARD:
		// ...;
		break;
	case Direction::LEFT:
		// ...;
		break;
	case Direction::RIGHT:
		// ...;
		break;
	case Direction::UP:
		// TODO U01.2: limit phi to ]-90,90[

		// TODO U01.3: remove the limit and modify Recalculate()

		// ...;
		break;
	case Direction::DOWN:
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