#include "MyProject.h"

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "Controllers/Devices/Mouse.h"
#include "Controllers/Devices/Keyboard.h"

#include "Graphics/Material/Material.h"

#include "Project/Geometry.h"

namespace PrakCG {

	/////////////////////////////////////////////////////////////////
	// plugin initialization
	/////////////////////////////////////////////////////////////////

	// constructor: initialization
	std::vector<Circle2D> circleList;
	MyProject::MyProject() :
		coordSystem(-10, 10, -10, 10, -10, 10),
		camera(),
		wireframeOn(false),
		ambLightOn(false),
		dirLightOn(false)
	{
		// enable the rendering of the coordinate system
		coordSystem.Enable(true);

		// select the common shader
		shader = Shader("res/shaders/object.shader");

		// init lamps
		SetupLights();

		Circle2D circle1 = Circle2D(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f);
		Circle2D circle2 = Circle2D(glm::vec3(9.0f, 0.0f, 0.0f), 3.0f);
		Circle2D::TangentPoints C0C1Tangents = circle1.GetTangentPointsBetweenCircle(circle2, true);
		circle1.printPoint(C0C1Tangents.T1);
		circle1.printPoint(C0C1Tangents.T2);
		Circle2D::TangentPoints C1C0Tangents = circle2.GetTangentPointsBetweenCircle(circle1, true);
		circle1.printPoint(C1C0Tangents.T1);
		circle1.printPoint(C1C0Tangents.T2);

		circle1.SetArc(C0C1Tangents.T1, C1C0Tangents.T2, Circle2D::clockwise);
		circle2.SetArc(C1C0Tangents.T2, C0C1Tangents.T1, Circle2D::clockwise);

		circle1.printInfo();
		circle2.printInfo();

		circle1.InitSpheresOnCircle(circle1.teethSize, 0.05f);
		circleList.push_back(circle1);
		circle2.InitSpheresOnCircle(circle2.teethSize, 0.05f);
		circleList.push_back(circle2);

	}

	// destructor: cleanup 
	MyProject::~MyProject() {
		coordSystem.Cleanup();
		shader.Cleanup();
	}

	void MyProject::OnUpdate(double deltaTime) {
		Interaction(deltaTime);
		Simulation(deltaTime);
	}

	// GUI hook:
	void MyProject::OnImGuiRender() {

		Dialog();

		ImGui::Separator();
		float fps = ImGui::GetIO().Framerate;
		if (fps < 0.00001f) fps = 0.00001f; // avoid div by zero
		ImGui::Text("Perf: %.1f FPS (%.3fms/frame)", fps, 1000.0f / fps);
	}

	void MyProject::OnRender() {
		PrepareFrame();
		RenderLights();
		Render();
	}

	// framebuffer hook: 
	// called when framebuffer / window size has changed
	void MyProject::OnFrameBufferChanged(unsigned int width, unsigned int height) {
		camera.SetAspect((float)width / (float)height);
		camera.UpdateProjection();
	}

	/////////////////////////////////////////////////////////////////
	// preparatiion the new frame 
	/////////////////////////////////////////////////////////////////

	// clear frame buffer, set up camera and projection matrix in shader
	void MyProject::PrepareFrame()
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
	void MyProject::SetupLights()
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
	void MyProject::RenderLights()
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
	void MyProject::Interaction(double deltaTime)
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
	void MyProject::Dialog()
	{
		// toggle the lights via GUI
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::Text("Select the active lights: ");
		ImGui::Checkbox("Global Ambient Light", &ambLightOn);
		ImGui::Checkbox("Directional Light", &dirLightOn);
		ImGui::NewLine();

		//// TODO U00.1: add GUI elements for camera adjustments (pos, center, up)
		//ImGui::DragFloat3("Position: ", &cPosDiff.x, 0.05f);
		//ImGui::DragFloat3("Center: ", &cCenterDiff.x, 0.05f);
		//ImGui::DragFloat3("Up: ", &cUpDiff.x, 0.05f);
	}

	// update the scene: 
	// implement your simulation/animation logic here
	void MyProject::Simulation(double deltaTime)
	{
	}

	// render one frame of your scene here
	// coord base = world coordinates
	// the camera has already been set in PrepareFrame()
	void MyProject::Render()
	{
		/*matrixStack.PushMatrix();
		{
			matrixStack.Scale(6.0f, 6.0f, 6.0f);
		}
		matrixStack.PopMatrix();*/
		for( size_t i = 0; i < circleList.size(); i++) {
			circleList[i].Render();
		}

	}
}