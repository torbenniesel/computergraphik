#pragma once

#include "Graphics/Models/COSAxles.hpp"
#include "Graphics/Models/Cone.hpp"

class Coordinatesystem
{
private:
	bool enabled;

	COSAxles cosAxles;
	Cone redCone;
	Cone greenCone;
	Cone blueCone;

public:
	Coordinatesystem();
	Coordinatesystem(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	~Coordinatesystem();

	inline bool IsEnabled() { return enabled; };
	inline void Enable(bool value) { enabled = value; };

	inline void RenderAxles(Shader shader, glm::mat4 model) {
		cosAxles.Render(shader, model);
		RenderSpikes(shader, model);
	};

	inline void RenderSpikes(Shader shader, glm::mat4 model) {
		redCone.SetEmission(1.0f);
		redCone.Render(shader, model);
		greenCone.SetEmission(1.0f);
		greenCone.Render(shader, model);
		blueCone.SetEmission(1.0f);
		blueCone.Render(shader, model);
	};

	void Cleanup();
};

