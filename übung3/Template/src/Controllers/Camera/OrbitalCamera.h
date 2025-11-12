#pragma once
#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "Controllers/Camera/Camera.h"
#include "Graphics/COS/CoordinateSystem.h"
#include "Controllers/Devices/Mouse.h"

#define initialAlpha 0.0f
#define initialPhi 0.0f
#define initialDistance 35.0f

enum class Direction {
	NONE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class OrbitalCamera : public Camera
{
private:
	// the internal camera parameters in spherical coordinates, see exercise sheet
	float alpha;	 // Longitude in degrees
	float phi;	     // Latitude  in degrees	
	float distance;  // distance between camera position and center point in meters

	// internal helpers for computation of cam position, viewing direction and cam UP direction
	const glm::vec3 earthYAxis = glm::vec3(0.0f, 1.0f, 0.0f); // the global UP direction
	glm::vec3 front; // the resulting viewing direction
	glm::vec3 right; // the resulting direction to the right 
	
	// sensitivity 
	float sensitivity = 10.0f; // larger value to move faster

public:
	// the initial camera, parameters see above
	OrbitalCamera(
		float alpha = initialAlpha,
		float phi = initialPhi,
		float distance = initialDistance
	);
	~OrbitalCamera();

	// determination of the new Cartesian coordinates from the spherical coordinates 
	void Recalculate();

	// move the camera position in a given direction, in earth coordinates  
	// UP, DOWN affect Latitude
	// LEFT, RIGHT affect Longitude
	// FORWARD, BACKWARD affect DISTANCE
	void Move(Direction dir = Direction::NONE, double deltaTime = 0.0f);

	// move the camera position using the mouse
	// affect Latitude and Logitude
	// dir.x,dir.y : horizontal and vertical parts of the mouse movement 
	// dir.z : forward/backward part of the mouse movement
	void Move(glm::vec3 dir, double deltaTime);

	// move the center point in camera coordinate system
	// UP, DOWN moves along UP axis
	// LEFT, RIGHT moves along RIGHT axis
	// FORWARD, BACKWARD moves along FRONT axis
	void MoveCenter(Direction dir = Direction::NONE, double deltaTime = 0.0f);

	// TODO U03.2: declare a method for moving the center with the mouse
	// move the center point using the mouse
	// dir.x,dir.y : horizontal and vertical parts of the mouse movement 
	// dir.z : forward/backward part of the mouse movement
	// ...
	void MoveCenter(glm::vec3 dir, double deltaTime);

	// restore initial camera settings
	void Reset();

};

#endif