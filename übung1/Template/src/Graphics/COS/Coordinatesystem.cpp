#include "Graphics/COS/Coordinatesystem.h"

#include <vector>
#include <iostream>

void Coordinatesystem::Cleanup()
{
	cosAxles.Cleanup();
	redCone.Cleanup();
	greenCone.Cleanup();
	blueCone.Cleanup();
}

Coordinatesystem::Coordinatesystem() :
	redCone(0.3f, 1.0f, 20, 3, Color::red, glm::vec3(10, 0, 0), glm::vec3(1.0f), glm::vec3(0.0f, 90.0f, 0.0f)),
	greenCone(0.3f, 1.0f, 20, 3, Color::green, glm::vec3(0, 10, 0), glm::vec3(1.0f), glm::vec3(-90.0f, 0.0f, 0.0f)),
	blueCone(0.3f, 1.0f, 20, 3, Color::blue, glm::vec3(0, 0, 10), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 90.0f)),
	cosAxles(-8, 10, -8, 10, -8, 10),
	enabled(true)
{
}

Coordinatesystem::Coordinatesystem(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) :
	redCone(0.3f, 1.0f, 20, 3, Color::red, glm::vec3(maxX, 0, 0), glm::vec3(1.0f), glm::vec3(0.0f, 90.0f, 0.0f)),
	greenCone(0.3f, 1.0f, 20, 3, Color::green, glm::vec3(0, maxY, 0), glm::vec3(1.0f), glm::vec3(-90.0f, 0.0f, 0.0f)),
	blueCone(0.3f, 1.0f, 20, 3, Color::blue, glm::vec3(0, 0, maxZ), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 90.0f)),
	cosAxles(minX, maxX, minY, maxY, minZ, maxZ),
	enabled(true)
{
}

Coordinatesystem::~Coordinatesystem() {

}