#pragma once

#include "Plugins/Plugin.h"
#include "Globals/Globals.h"

#include "Graphics/MatrixStack/MatrixStack.h"

#include "Graphics/COS/Coordinatesystem.h"
#include "Graphics/Light/Light.h"

#include "Controllers/Camera/Camera.h"
#include "Controllers/Camera/OrbitalCamera.h"

#include "Graphics/Models/Cylinder.hpp"
#include "Graphics/Models/Cube.hpp"
#include "Graphics/Models/Sphere.hpp"

namespace PrakCG {

	class Lesson1 : public Plugin, Globals
	{
	public:
		Lesson1();
		~Lesson1();

		// hooks that are called from the framework
		// to update the frame 
		void OnUpdate(double deltaTime) override;
		// to render the frame
		void OnRender() override;
		// for the GUI
		void OnImGuiRender() override;
		// Framebuffer changed callback
		void OnFrameBufferChanged(unsigned int width, unsigned int height) override;

	private:
		// clear frame buffer, set background color, render coordinate system
		void PrepareFrame();
		// set light paramaters
		void SetupLights();
		// transfer lights to shader uniforms
		void RenderLights();
				

		// keyboard and direct! mouse interaction
		void Interaction(double deltaTime);
		// GUI interaction
		void Dialog();
		// set up scene: animation 
		void Simulation(double deltaTime);
		// render scene
		void Render();

		// member variables
		Coordinatesystem coordSystem;
		bool wireframeOn;

		// light switches
		bool ambLightOn;
		bool dirLightOn;

		// default lights
		AmbientLight ambientLight; 
		DirLight dirLight;

		// declaration of Cube instance
		Cube cube;
		
		// the default camera
		Camera camera;

		// the orbital camera
		OrbitalCamera orbitCamera;
		// save the value of the mouse value since we need a relative value
		float lastScrollValue;
		
		// GUI: camera selection 
		bool useOrbitalCamera;

		// GUI: displacement of the default camera
		glm::vec3 cPosDiff;
		glm::vec3 cCenterDiff;
		glm::vec3 cUpDiff;

		// GUI: animation of the orbital camera
		bool xAnimation;
		bool yAnimation;
		float animationSpeed;

		// Prev Frame Mouse Pos
		float lastMouseX;
		float lastMouseY;

		// Stuff
		void printVector(glm::vec3 v, std::string name = "Vector") {
			printf("%s: %4.2f %4.2f %4.2f\n", name, v.x, v.y, v.z);
		};

		// draw a simple snowman using spheres and cylinders
		void DrawSnowman();

		// TODO U03.4: declare the needed geometry
		// ...
		std::vector<Model> snowMan = std::vector<Model>();
		void InitSnowman(glm::vec3 origin);
		

	};
}