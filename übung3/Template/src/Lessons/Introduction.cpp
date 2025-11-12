#include "Introduction.h"

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "Controllers/Devices/Mouse.h"
#include "Controllers/Devices/Keyboard.h"

#include "Graphics/Material/Material.h"

namespace PrakCG {

	/////////////////////////////////////////////////////////////////
	// plugin initialization
	/////////////////////////////////////////////////////////////////

	// constructor: initialization
	Introduction::Introduction() :
		coordSystem(-10, 10, -10, 10, -10, 10),
		camera(),
		wireframeOn(false),
		ambLightOn(false),
		dirLightOn(false),

		cPosDiff(0),
		cCenterDiff(0),
		cUpDiff(0)
	{
		// enable the rendering of the coordinate system
		coordSystem.Enable(true);
		
		// select the common shader
		shader = Shader("res/shaders/object.shader");
		
		// init lamps
		SetupLights();
		
		// init the cube model, use wood texture
		cube = Cube(1.0f, { "res/textures/wood.jpg" }, { aiTextureType_DIFFUSE });
	}

	// destructor: cleanup 
	Introduction::~Introduction() {
		cube.Cleanup();
		coordSystem.Cleanup();
		shader.Cleanup();
	}

	/////////////////////////////////////////////////////////////////
	// functions called by the main function
	/////////////////////////////////////////////////////////////////

	// update hook: keyboard interaction and simulation
	// get keyboard and mouse interaction and call update function
	void Introduction::OnUpdate(double deltaTime) {
		Interaction(deltaTime);
		Simulation(deltaTime);
	}

	// GUI hook: 
	// implement your GUI elements here
	void Introduction::OnImGuiRender() {

		Dialog();

		ImGui::Separator();
		float fps = ImGui::GetIO().Framerate; 
		if (fps < 0.00001f) fps = 0.00001f; // avoid div by zero
		ImGui::Text("Perf: %.1f FPS (%.3fms/frame)", fps, 1000.0f / fps);
	}

	// render hook: render one frame: 
	//  - clear framebuffer, 
	//  - set up lights, 
	//  - render coordinate system, 
	//  - render scene 
	void Introduction::OnRender() {
		PrepareFrame();
		RenderLights();
		Render();
	}

	// framebuffer hook: 
	// called when framebuffer / window size has changed
	void Introduction::OnFrameBufferChanged(unsigned int width, unsigned int height) {
		camera.SetAspect((float)width / (float)height);
		camera.UpdateProjection();
	}

	/////////////////////////////////////////////////////////////////
	// preparatiion the new frame 
	/////////////////////////////////////////////////////////////////
	
	// clear frame buffer, set up camera and projection matrix in shader
	void Introduction::PrepareFrame()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Render(shader);

		if (this->coordSystem.IsEnabled()) {
			coordSystem.RenderAxles(shader, matrixStack.GetMatrix());
		}
	}

	/////////////////////////////////////////////////////////////////
	// lights
	/////////////////////////////////////////////////////////////////

	// set light parameters here
	void Introduction::SetupLights()
	{
		ambientLight.ambient = glm::vec4(0, 0, 0, 1.0f);

		dirLight = {
			true,
			glm::vec3(-1.0f, -1.0f, -1.0f),
			glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		};
		dirLightOn = true;
	}

	// pass light settings to the shader uniforms
	void Introduction::RenderLights()
	{
		// set Lights
		shader.Bind();

		// global Ambient Light
		if (ambLightOn)
			ambientLight.ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		else
			ambientLight.ambient = glm::vec4(0, 0, 0, 1.0f);
		ambientLight.Render(shader);

		// directional Light
		if (dirLightOn) {
			shader.SetInt("numberDirLights", 2);
			// directional Light Animation
			dirLight.direction = glm::vec3(-1.0f, -1.0f, -1.0f);
			dirLight.ambient = glm::vec4(0.2f);
			dirLight.diffuse = glm::vec4(1.0f);
			dirLight.specular = glm::vec4(1.0f);
		}
		else
			shader.SetInt("numberDirLights", 0);
		dirLight.Render(shader);
	}

	/////////////////////////////////////////////////////////////////
	// for now, all the student code is below, 
	//   - animate your scene in Simulation()
	//   - render your scene in Render()
	//   - implement your GUI elements in OnImGuiRender()
	/////////////////////////////////////////////////////////////////

	// keyboard and direct!! mouse interaction 
	// do not implement the GUI elements here, for the GUI use Dialog
	void Introduction::Interaction(double deltaTime)
	{
		// toggle coordinate system
		if (KeyBoard::keyWentDown(GLFW_KEY_K))
			coordSystem.Enable(!coordSystem.IsEnabled());

		// toggle wireframe
		if (KeyBoard::keyWentDown(GLFW_KEY_W)) {
			wireframeOn = !wireframeOn;
			if (wireframeOn) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}

		// toggle the lights via keyboard
		if (KeyBoard::keyWentDown(GLFW_KEY_F1)) {
			ambLightOn = !ambLightOn;
		}
		if (KeyBoard::keyWentDown(GLFW_KEY_F2)) {
			dirLightOn = !dirLightOn;
		}

		// zooming with the mouse wheel:
		// modify the "focal lenght" of the camera  
		if (Mouse::hasScrolled) {
			Mouse::hasScrolled = false;
			camera.SetFovy(Mouse::scrollValue);
			camera.UpdateProjection();
		}
	}

	// GUI interaction
	// implement your GUI elements and logic here
	void Introduction::Dialog() 
	{
		// toggle the lights via GUI
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::Text("Select the active lights: ");
		ImGui::Checkbox("Global Ambient Light", &ambLightOn);
		ImGui::Checkbox("Directional Light", &dirLightOn);
		ImGui::NewLine();

		ImGui::DragFloat3("Position: ", &cPosDiff.x, 0.05f);
		ImGui::DragFloat3("Center: ", &cCenterDiff.x, 0.05f);
		ImGui::DragFloat3("Up: ", &cUpDiff.x, 0.05f);
	}

	// update the scene: 
	// implement your simulation/animation logic here
	void Introduction::Simulation(double deltaTime)
	{
		// get the current camera position
		glm::vec3 cPos = camera.GetPosition();
		cPos = cPos + cPosDiff;
		cPosDiff = glm::vec3(0);

		// get the current center point
		glm::vec3 cCenter = camera.GetCenter();
		cCenter = cCenter + cCenterDiff;
		cCenterDiff = glm::vec3(0);

		// get the current up vector
		glm::vec3 cUp = camera.GetUp();
		cUp = cUp + cUpDiff;
		cUpDiff = glm::vec3(0);

		// update the camera settings
		camera.SetPosition(cPos);
		camera.SetCenter(cCenter);
		camera.SetUp(cUp);
		camera.UpdateView();
	}

	// render one frame of your scene here
	// coord base = world coordinates
	// the camera has already been set in PrepareFrame()
	void Introduction::Render()
	{
		matrixStack.PushMatrix();
		{
			matrixStack.Scale(6.0f, 6.0f, 6.0f);
			cube.Render(shader, matrixStack.GetMatrix());
		}
		matrixStack.PopMatrix();
	}
}