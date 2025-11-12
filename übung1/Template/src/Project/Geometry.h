#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "glm/glm.hpp"
#include <cmath>
#include <format>
#include "Graphics/MatrixStack/MatrixStack.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Models/Sphere.hpp"
#include "Graphics/Models/Cube.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



class Geometry {
public:
	Geometry();
	~Geometry();

	void Cleanup();

};

class Circle2D {
public:
	enum Direction {
		clockwise = -1,
		counterClockwise = 1,
	};

	struct TangentPoints {
		glm::vec2 T1; // Tangentenpunkt auf dem ersten Kreis
		glm::vec2 T2; // Tangentenpunkt auf dem zweiten Kreis
	};

	glm::vec2 position = glm::vec2(0);
	float radius = 1;
	Direction direction = counterClockwise;

	float startAngle = 0.0f;
	float endAngle = 0.0f;
	bool hasStartAngle = false;
	bool hasEndAngle = false;
	bool hasArc = false;

	float teethSize = 0.22f;

	


	Circle2D(glm::vec2 pos, float r) : position(pos), radius(r) {}

	~Circle2D() {}

	void printInfo() {
		printf("Circle2D: Position(%.2f, %.2f), Radius: %.2f\n", position.x, position.y, radius);
		if (hasStartAngle) {
			printf("  Start Angle: %.2f rad\n", startAngle);
			// Startpoint
			printf("  Start Point: (%.2f, %.2f)\n", GetPointAtAngle(startAngle).x, GetPointAtAngle(startAngle).y);
		}
		if (hasEndAngle) {
			printf("  End Angle: %.2f rad\n", endAngle);
			printf("  End Point: (%.2f, %.2f)\n", GetPointAtAngle(endAngle).x, GetPointAtAngle(endAngle).y);
		}
		if (hasStartAngle && hasEndAngle) {
			printf("  Direction: %s\n", direction == clockwise ? "Clockwise" : "Counter-Clockwise");
			printf("  Arc Length: %.2f\n", getArcLength());
		}

		// Print 5 points along the arc
		if (hasStartAngle && hasEndAngle) {
			int numPoints = 5;
			printf("  Points along arc:\n");
			float arcLength = getArcLength();
			for (int i = 0; i <= numPoints; ++i) {
				float distance = (arcLength / numPoints) * i;
				glm::vec2 point = GetPointAtArcDistanceFromStart(distance);
				printf("    Point %d: (%.2f, %.2f)\n", i, point.x, point.y);
			}
		}
	}

	void printPoint(glm::vec2 point) {
		printf("Point: (%.2f, %.2f)\n", point.x, point.y);
	}

	void printAngleRad(float angleRad) {
		printf("Angle: %.2f rad\n", angleRad);
	}

	void printAngleDeg(float angleRad) {
		float angleDeg = angleRad * (180.0f / M_PI);
		printf("Angle: %.2f deg\n", angleDeg);
	}

	void SetStartAngle(glm::vec2 pointOnCircle) {
		glm::vec2 dir = glm::normalize(pointOnCircle - position);
		startAngle = atan2(dir.y, dir.x);
		hasStartAngle = true;
	}

	void SetStartAngle(float angleRad) {
		startAngle = angleRad;
		hasStartAngle = true;
	}

	void SetEndAngle(glm::vec2 pointOnCircle) {
		glm::vec2 dir = glm::normalize(pointOnCircle - position);
		endAngle = atan2(dir.y, dir.x);
		hasEndAngle = true;
	}

	void SetEndAngle(float angleRad) {
		endAngle = angleRad;
		hasEndAngle = true;
	}

	void SetDirection(Direction dir) {
		direction = dir;
	}

	void SetArc(float startAngleRad, float endAngleRad, Direction dir) {
		SetStartAngle(startAngleRad);
		SetEndAngle(endAngleRad);
		SetDirection(dir);
	}

	void SetArc(glm::vec2 startPoint, glm::vec2 endPoint, Direction dir) {
		SetStartAngle(startPoint);
		SetEndAngle(endPoint);
		SetDirection(dir);
	}

	void SetArcWithDistance(glm::vec2 startPoint, float arcDistance, Direction dir) {
		SetStartAngle(startPoint);
		float angleRad = startAngle + dir * (arcDistance / radius);
		SetEndAngle(angleRad);
		SetDirection(dir);
	}

	void SetArcWithDistance(float startAngleRad, float arcDistance, Direction dir) {
		SetStartAngle(startAngleRad);
		float angleRad = startAngle + dir * (arcDistance / radius);
		SetEndAngle(angleRad);
		SetDirection(dir);
	}

	void SetTeethSize(float size) {
		teethSize = size;
	}

	glm::vec2 GetPointAtAngle(float angleRad, float startAngle = 0) {
		return position + glm::vec2(cos(angleRad+startAngle), sin(angleRad+startAngle)) * radius;
	}

	glm::vec2 GetPointAtArcDistanceFromStart(float distance) {
		float angleRad = startAngle + direction * (distance / radius);
		return GetPointAtAngle(angleRad);
	}
	glm::vec2 GetPointAtArcDistanceFromEnd(float distance) {
		float angleRad = endAngle - direction * (distance / radius);
		return GetPointAtAngle(angleRad);
	}

	float getArcLength() {
		float TWO_PI = 2.0f * M_PI;

		// Handle the case of a full circle.
		if (startAngle == endAngle) {
			return TWO_PI * radius;
		}

		// Normalize angles to the range [0, 2*PI)
		float start = fmodf(startAngle, TWO_PI);
		if (start < 0) start += TWO_PI;

		float end = fmodf(endAngle, TWO_PI);
		if (end < 0) end += TWO_PI;

		float sweepAngle = 0.0f;

		if (direction == Direction::counterClockwise) {
			sweepAngle = (end >= start) ? (end - start) : (TWO_PI - start + end);
		}
		else {
			sweepAngle = (start >= end) ? (start - end) : (TWO_PI - end + start);
		}

		return sweepAngle * radius;
	}

	bool isPointOnArc(glm::vec2 point) {
		if (!hasStartAngle || !hasEndAngle) {
			return false;
		}
		glm::vec2 dir = glm::normalize(point - position);
		float angleRad = atan2(dir.y, dir.x);
		float start = startAngle;
		float end = endAngle;
		if (direction == clockwise) {
			if (start < end) {
				start += 2 * M_PI;
			}
			return angleRad <= start && angleRad >= end;
		}
		else {
			if (end < start) {
				end += 2 * M_PI;
			}
			return angleRad >= start && angleRad <= end;
		}
	}

	bool isDistanceOnArc(float distance) {
		if (!hasStartAngle || !hasEndAngle) {
			return false;
		}
		float arcLength = getArcLength();
		return distance >= 0.0f && distance <= arcLength;
	}

	bool isNextTeethOnArc(float distance) {
		if (!hasStartAngle || !hasEndAngle) {
			return false;
		}
		float nextDistance = distance + teethSize;
		return isDistanceOnArc(nextDistance);
	}

	glm::vec2 GetNextPointAtArcDistanceFromStart(float distance) {
		float angleRad = startAngle + direction * ((distance + teethSize) / radius);
		return GetPointAtAngle(angleRad);
	}

	// Find Outer Tangent Points to another Circle2D
	// Vector from this circle to the other circle
	TangentPoints GetTangentPointsBetweenCircle(Circle2D& otherCircle, bool leftTangent = true) {
		float distanceBetweenCenters = glm::length(otherCircle.position - position);
		float r1 = radius;
		float r2 = otherCircle.radius;
		float angleBetweenCenters = atan2(otherCircle.position.y - position.y, otherCircle.position.x - position.x);
		float angleOffset = acos((r1 - r2) / distanceBetweenCenters);
		float tangentAngle1, tangentAngle2;
		if (leftTangent) {
			tangentAngle1 = angleBetweenCenters + angleOffset;
			tangentAngle2 = angleBetweenCenters + angleOffset;
		}
		else {
			tangentAngle1 = angleBetweenCenters - angleOffset;
			tangentAngle2 = angleBetweenCenters - angleOffset;
		}
		glm::vec2 T1 = GetPointAtAngle(tangentAngle1);
		glm::vec2 T2 = otherCircle.GetPointAtAngle(tangentAngle2);

		return { T1, T2 };
	}



	Sphere s = Sphere(1.0f, 20, 20, Color::red);
	std::vector<Sphere> circleSpheres;
	std::vector<Sphere> arcSpheres;
	void InitSpheresOnCircle(float intervalDistance = 0.22f, float sphereRadius = 0.1f, int slices = 10, int stacks = 10) {
		circleSpheres.clear();
		arcSpheres.clear();
		// Spheres on full circle
		int numSpheres = static_cast<int>((2 * M_PI * radius) / intervalDistance);
		for (int i = 0; i < numSpheres; ++i) {
			float angleRad = (static_cast<float>(i) / numSpheres) * 2 * M_PI;
			glm::vec2 point = GetPointAtAngle(angleRad);
			Sphere sphere(sphereRadius, slices, stacks, Color::blue);
			sphere.SetPosition(glm::vec3(point, 0.0f));
			circleSpheres.push_back(sphere);
		}
		// Spheres on arc
		if (hasStartAngle && hasEndAngle) {
			float arcLength = getArcLength();
			int numArcSpheres = static_cast<int>(arcLength / intervalDistance);
			for (int i = 0; i < numArcSpheres; ++i) {
				float distance = (static_cast<float>(i) / numArcSpheres) * arcLength;
				glm::vec2 point = GetPointAtArcDistanceFromStart(distance);
				Sphere sphere(sphereRadius*1.5, slices, stacks, Color::red);
				sphere.SetPosition(glm::vec3(point, 0.0f));
				arcSpheres.push_back(sphere);
			}
		}
		// Add Start and End point spheres
		if (hasStartAngle) {
			glm::vec2 startPoint = GetPointAtAngle(startAngle);
			Sphere sphere(sphereRadius * 2.0f, slices, stacks, Color::green);
			sphere.SetPosition(glm::vec3(startPoint, 0.0f));
			arcSpheres.push_back(sphere);
		}
		if (hasEndAngle) {
			glm::vec2 endPoint = GetPointAtAngle(endAngle);
			Sphere sphere(sphereRadius * 2.0f, slices, stacks, Color::yellow);
			sphere.SetPosition(glm::vec3(endPoint, 0.0f));
			arcSpheres.push_back(sphere);
		}

	}

	void Render() {
		printf("Render Circle2D Spheres\n");

		for (auto& sphere : circleSpheres) {
			sphere.Render(PrakCG::Globals::shader, PrakCG::Globals::matrixStack.GetMatrix());
		}

		for (auto& sphere : arcSpheres) {
			sphere.Render(PrakCG::Globals::shader, PrakCG::Globals::matrixStack.GetMatrix());
		}

	}

	
};

#endif