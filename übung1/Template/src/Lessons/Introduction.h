#pragma once

#include "Plugins/Plugin.h"
#include "Globals/Globals.h"

#include "Graphics/MatrixStack/MatrixStack.h"

#include "Graphics/COS/Coordinatesystem.h"
#include "Graphics/Light/Light.h"

#include "Controllers/Camera/Camera.h"

#include "Graphics/Models/Cylinder.hpp"
#include "Graphics/Models/Cube.hpp"
#include "Graphics/Models/Sphere.hpp"

namespace PrakCG {

	class Introduction : public Plugin, Globals
	{
	public:
		Introduction();
		~Introduction();

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
		Camera camera;
		bool wireframeOn;

		// light switches
		bool ambLightOn;
		bool dirLightOn;

		// default lights
		AmbientLight ambientLight; 
		DirLight dirLight;

		// declaration of Cube instance
		Cube cube;

		// TODO U00.1: camera movement
		glm::vec3 cPosDiff;
		glm::vec3 cCenterDiff;
		glm::vec3 cUpDiff;
	};
}