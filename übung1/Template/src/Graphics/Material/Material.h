#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <assimp/scene.h>

/*
	material structure to contain lighting values for different materials
*/

struct Material {
	// lighting values
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emission;
	float shininess;

	/*
		static instances of common materials
	*/

	static Material emerald;
	static Material jade;
	static Material obsidian;
	static Material pearl;
	static Material ruby;
	static Material turquoise;
	static Material brass;
	static Material bronze;
	static Material chrome;
	static Material copper;
	static Material gold;
	static Material silver;
	static Material black_plastic;
	static Material red_plastic;
	static Material green_plastic;
	static Material blue_plastic;
	static Material cyan_plastic;
	static Material magenta_plastic;
	static Material yellow_plastic;
	static Material white_plastic;
	static Material black_rubber;
	static Material cyan_rubber;
	static Material green_rubber;
	static Material red_rubber;
	static Material white_rubber;
	static Material yellow_rubber;
	static Material grey_rubber;
	// function to mix two materials with a proportion
	static Material mix(Material m1, Material m2, float mix = 0.5f);
};

struct Color {
	static aiColor4D white;
	static aiColor4D gray;
	static aiColor4D black;
	static aiColor4D red;
	static aiColor4D green;
	static aiColor4D blue;
	static aiColor4D lightblue;

	static aiColor4D maroon;
	static aiColor4D pink;
	static aiColor4D brown;
	static aiColor4D orange;
	static aiColor4D apricot;
	static aiColor4D olive;
	static aiColor4D beige;
	static aiColor4D lime;
	static aiColor4D mint;
	static aiColor4D teal;
	static aiColor4D cyan;
	static aiColor4D purple;
	static aiColor4D lavender;
	static aiColor4D magenta;
	static aiColor4D yellow;

	static aiColor4D mix(aiColor4D c1, aiColor4D c2, float mix = 0.5f);
};

#endif
