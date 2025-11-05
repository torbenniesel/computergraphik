#include "Lesson_01.h"

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "Controllers/Devices/Mouse.h"
#include "Controllers/Devices/Keyboard.h"

#include "Graphics/Material/Material.h"

#include "Graphics/Objects/ChainManager.h"

namespace PrakCG {

	/////////////////////////////////////////////////////////////////
	// plugin initialization
	/////////////////////////////////////////////////////////////////

	// constructor: initialization
	std::vector<ChainLink> chainLinks;
	std::vector<Sphere> sphereList;
	std::vector<Model> chainLinkList;
	Lesson1::Lesson1() :
		coordSystem(-10, 10, -10, 10, -10, 10),
		wireframeOn(false),
		ambLightOn(false),
		dirLightOn(false),

		// TODO U00.1: initialization of the vectors
		cPosDiff(0),
		cCenterDiff(0),
		cUpDiff(0),

		camera(),
		orbitCamera(),
		useOrbitalCamera(false)

	{
		// enable the rendering of the coordinate system
		coordSystem.Enable(true);
		
		// select the common shader
		shader = Shader("res/shaders/object.shader");
		
		// init lamps
		SetupLights();

		chainLinkOut = Model(glm::vec3(1.0f, 0, 0));
		chainLinkOut.LoadModel("res/Blender/CHAIN_LINK_OUT.fbx");

		chainLinkIn = Model(glm::vec3(1.0f, 0.22f, 0));
		chainLinkIn.LoadModel("res/Blender/CHAIN_LINK_IN.fbx");
		

		gearBig = Model(glm::vec3(0, 0, 0));
		gearBig.LoadModel("res/Blender/GEAR_BIG.fbx");

		gearSmall = Model(glm::vec3(0, 0, 0));
		gearSmall.LoadModel("res/Blender/GEAR_SMALL.fbx");


		ChainManager chainManager = ChainManager();
		chainLinks = chainManager.CreateChainLinks();
		float size = chainLinks.size();
		printf("Size= %4.2f \n", size);
		
		//Create spheres for each chainLink
		int index = 0;
		for (const auto& link : chainLinks) {
			
			// Create a small sphere at each chain link position
			// Convert 2D position to 3D (using z = 0)
			glm::vec3 spherePos = glm::vec3(link.position.x, link.position.y, 0.0f);

			// Create sphere with small radius, positioned at the link location
			//Sphere sphere(
			//	0.2f,           // radius
			//	20,             // slices
			//	20,             // stacks
			//	Color::blue,    // color
			//	spherePos,      // position
			//	glm::vec3(1.0f), // size (no scaling)
			//	glm::vec3(0.0f)  // rotation
			//);
			if (index % 2 == 0) {
				Model chainLinkOutCopy = chainLinkOut;
				chainLinkOutCopy.SetPosition(spherePos);
				chainLinkList.push_back(chainLinkOutCopy);
			}
			else {
				Model chainLinkInCopy = chainLinkIn;
				chainLinkInCopy.SetPosition(spherePos);
				chainLinkList.push_back(chainLinkInCopy);
			}

			
			
			index++;
			//glm::vec2 newSpherePos = link.position + glm::vec2(cos(link.rotation.x), sin(link.rotation.x)) * 0.2f;

			//Sphere sphere2(
			//	0.1f,           // radius
			//	20,             // slices
			//	20,             // stacks
			//	Color::green,    // color
			//	glm::vec3(newSpherePos.x, newSpherePos.y, 0.0f),
			//	glm::vec3(1.0f), // size (no scaling)
			//	glm::vec3(0.0f)  // rotation
			//);
			//sphereList.push_back(sphere2);

			//newSpherePos = link.position + glm::vec2(cos(link.rotation.x), sin(link.rotation.x)) * 0.4f;

			//Sphere sphere3(
			//	0.1f,           // radius
			//	20,             // slices
			//	20,             // stacks
			//	Color::green,    // color
			//	glm::vec3(newSpherePos.x, newSpherePos.y, 0.0f),
			//	glm::vec3(1.0f), // size (no scaling)
			//	glm::vec3(0.0f)  // rotation
			//);
			//sphereList.push_back(sphere3);

			//newSpherePos = link.position + glm::vec2(cos(link.rotation.x), sin(link.rotation.x)) * 0.6f;

			//Sphere sphere4(
			//	0.1f,           // radius
			//	20,             // slices
			//	20,             // stacks
			//	Color::green,    // color
			//	glm::vec3(newSpherePos.x, newSpherePos.y, 0.0f),
			//	glm::vec3(1.0f), // size (no scaling)
			//	glm::vec3(0.0f)  // rotation
			//);
			//sphereList.push_back(sphere4);
		}

		 
		
		// init the cube model, use wood texture
		cube = Cube(0.001f, { "res/textures/wood.jpg" }, { aiTextureType_DIFFUSE }, glm::vec3(0,0,0));
		cube.SetAlpha(0);

		/*customModel = Model(glm::vec3(0, 0, 0));
		customModel.LoadModel("res/Blender/chainlink.fbx");
		customModel.SetAlpha(0.0f);
		customModel.SetSize(glm::vec3(0.1f));*/

		//cylinder = Cylinder(1.0f, 2.0f, 3, Color::blue);
		//cylinder2 = Cylinder(1.0f, 2.0f, 3, Color::green, glm::vec3(1.5f, 0, 0), glm::vec3(1.0f), glm::vec3(0));
	}

	// destructor: cleanup 
	Lesson1::~Lesson1() {
		//cube.Cleanup();
		customModel.Cleanup();
		coordSystem.Cleanup();
		shader.Cleanup();
	}

	/////////////////////////////////////////////////////////////////
	// functions called by the main function
	/////////////////////////////////////////////////////////////////

	// update hook: keyboard interaction and simulation
	// get keyboard and mouse interaction and call update function
	void Lesson1::OnUpdate(double deltaTime) {
		Interaction(deltaTime);
		Simulation(deltaTime);
	}

	// GUI hook: 
	// implement your GUI elements here
	void Lesson1::OnImGuiRender() {

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
	void Lesson1::OnRender() {
		PrepareFrame();
		RenderLights();
		Render();
	}

	// framebuffer hook: 
	// called when framebuffer / window size has changed
	void Lesson1::OnFrameBufferChanged(unsigned int width, unsigned int height) {
		camera.SetAspect((float)width / (float)height);
		orbitCamera.SetAspect((float)width / (float)height);
		camera.UpdateProjection();
		orbitCamera.UpdateProjection();
	}

	/////////////////////////////////////////////////////////////////
	// preparatiion the new frame 
	/////////////////////////////////////////////////////////////////
	
	// clear frame buffer, set up camera and projection matrix in shader
	void Lesson1::PrepareFrame()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		if (useOrbitalCamera)
			orbitCamera.Render(shader);
		else 
			camera.Render(shader);

		if (this->coordSystem.IsEnabled()) {
			coordSystem.RenderAxles(shader, matrixStack.GetMatrix());
		}
	}

	/////////////////////////////////////////////////////////////////
	// lights
	/////////////////////////////////////////////////////////////////

	// set light parameters here
	void Lesson1::SetupLights()
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
	void Lesson1::RenderLights()
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
	void Lesson1::Interaction(double deltaTime)
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

		// Catch L-Alt
		if (KeyBoard::key(GLFW_KEY_LEFT_CONTROL)) {
			if (KeyBoard::key(GLFW_KEY_PAGE_UP)) {
				orbitCamera.MoveCenter(Direction::FORWARD, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_PAGE_DOWN)) {
				orbitCamera.MoveCenter(Direction::BACKWARD, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_UP)) {
				orbitCamera.MoveCenter(Direction::UP, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_DOWN)) {
				orbitCamera.MoveCenter(Direction::DOWN, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_LEFT)) {
				orbitCamera.MoveCenter(Direction::LEFT, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_RIGHT)) {
				orbitCamera.MoveCenter(Direction::RIGHT, deltaTime);
			}
		}
		else {
			// move orbitCamera position
			if (KeyBoard::key(GLFW_KEY_PAGE_UP)) {
				orbitCamera.Move(Direction::FORWARD, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_PAGE_DOWN)) {
				orbitCamera.Move(Direction::BACKWARD, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_LEFT)) {
				orbitCamera.Move(Direction::LEFT, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_RIGHT)) {
				orbitCamera.Move(Direction::RIGHT, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_UP)) {
				orbitCamera.Move(Direction::UP, deltaTime);
			}
			if (KeyBoard::key(GLFW_KEY_DOWN)) {
				orbitCamera.Move(Direction::DOWN, deltaTime);
			}
		}

		float movingSpeed = 1.0f;		// Units per second
		float rotationSpeed = 90.0f;	// Degrees per second
		float moveStep = 0.2f;			// How many units to move per key press (20%)
		float rotationStep = 15.0f;		// How many degrees to rotate per key press
		// --- ROTATION LOGIC ---
		if (allowRotating == true) {
			if (KeyBoard::key(GLFW_KEY_RIGHT)) {
				chainLinkIn.Rotate(glm::vec3(0.0f, -rotationSpeed * (float)deltaTime, 0.0f));
			}
			if (KeyBoard::key(GLFW_KEY_LEFT)) {
				chainLinkIn.Rotate(glm::vec3(0.0f, rotationSpeed * (float)deltaTime, 0.0f));
			}

			if (KeyBoard::key(GLFW_KEY_UP)) {
				chainLinkIn.Rotate(glm::vec3(0.0f, 0.0f, rotationSpeed * (float)deltaTime));
			}
			if (KeyBoard::key(GLFW_KEY_DOWN)) {
				chainLinkIn.Rotate(glm::vec3(0.0f, 0.0f, -rotationSpeed * (float)deltaTime));
			}
		}

		// --- MOVEMENT LOGIC ---
		if (allowMoving == true) {
			if (KeyBoard::key(GLFW_KEY_RIGHT)) {
				chainLinkIn.Translate(glm::vec3(movingSpeed * (float)deltaTime, 0.0f, 0.0f));
			}
			if (KeyBoard::key(GLFW_KEY_LEFT)) {
				chainLinkIn.Translate(glm::vec3(-movingSpeed * (float)deltaTime, 0.0f, 0.0f));
			}

			if (KeyBoard::key(GLFW_KEY_UP) && !KeyBoard::key(GLFW_KEY_LEFT_SHIFT)) {
				chainLinkIn.Translate(glm::vec3(0.0f, 0.0f, -movingSpeed * (float)deltaTime));
			}
			if (KeyBoard::key(GLFW_KEY_UP) && KeyBoard::key(GLFW_KEY_LEFT_SHIFT)) {
				chainLinkIn.Translate(glm::vec3(0.0f, movingSpeed * (float)deltaTime, 0.0f));
			}

			if (KeyBoard::key(GLFW_KEY_DOWN) && !KeyBoard::key(GLFW_KEY_LEFT_SHIFT)) {
				chainLinkIn.Translate(glm::vec3(0.0f, 0.0f, movingSpeed * (float)deltaTime));
			}
			if (KeyBoard::key(GLFW_KEY_DOWN) && KeyBoard::key(GLFW_KEY_LEFT_SHIFT)) {
				chainLinkIn.Translate(glm::vec3(0.0f, -movingSpeed * (float)deltaTime, 0.0f));
			}
		}

		if (KeyBoard::key(GLFW_KEY_W)) {
			int index = 0;
			for (auto& chainLink : chainLinkList) {
				glm::vec3 pos = chainLinkIn.GetPosition();
				if (index == 0) {
					printf("Pos: (%4.2f, %4.2f, %4.2f)  Delta: %4.2f\n", pos.x, pos.y, pos.z, (float)deltaTime);
				}
				float movingSpeed = 1.0f;

				chainLinkIn.SetPosition(glm::vec3(pos.x, pos.y + movingSpeed * (float)deltaTime, pos.z));
				index++;
			}
			
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
	void Lesson1::Dialog() 
	{
		// toggle the lights via GUI
		ImGui::Separator();
		ImGui::NewLine();
		ImGui::Text("Select the active lights: ");
		ImGui::Checkbox("Global Ambient Light", &ambLightOn);
		ImGui::Checkbox("Directional Light", &dirLightOn);
		if (ImGui::Checkbox("Allow movement by arrow", &allowMoving)) {
			if (allowMoving) {
				allowRotating = false;
			}
		}
		if (ImGui::Checkbox("Allow rotate by arrow", &allowRotating)) {
			if (allowRotating) {
				allowMoving = false;
			}
		}
		ImGui::NewLine();

		if (ImGui::RadioButton("Default cam", useOrbitalCamera == false)) {
			useOrbitalCamera = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("OrbitalCamera", useOrbitalCamera == true)) {
			useOrbitalCamera = true;
		}

		
		if (!useOrbitalCamera) {
			// TODO U00.1: add GUI elements for camera adjustments (pos, center, up)
			ImGui::DragFloat3("Position: ", &cPosDiff.x, 0.05f);
			ImGui::DragFloat3("Center: ", &cCenterDiff.x, 0.05f);
			ImGui::DragFloat3("Up: ", &cUpDiff.x, 0.05f);
		}
		else {
			ImGui::Text("Usage: ");
			ImGui::Text("  - cursor keys: move camera position left, right, up, down");
			ImGui::Text("  - PageUp, PageDown: move camera forward, backward");
		}

	}

	// update the scene: 
	// implement your simulation/animation logic here
	void Lesson1::Simulation(double deltaTime)
	{
		// TODO U00.1: calculate the new camera parameters
		// and update the private object "camera"
		// ...
		
	}

	// render one frame of your scene here
	// coord base = world coordinates
	// the camera has already been set in PrepareFrame()
	void Lesson1::Render()
	{
		matrixStack.PushMatrix();
		{
			matrixStack.Scale(1.0f, 1.0f, 1.0f);
			//cube.Render(shader, matrixStack.GetMatrix());
			//customModel.Render(shader, matrixStack.GetMatrix());
			//cylinder.Render(shader, matrixStack.GetMatrix());
			//cylinder2.Render(shader, matrixStack.GetMatrix());
			chainLinkIn.Render(shader, matrixStack.GetMatrix());
			chainLinkOut.Render(shader, matrixStack.GetMatrix());
			//gearBig.Render(shader, matrixStack.GetMatrix());
			//gearSmall.Render(shader, matrixStack.GetMatrix());
		}
		

		/*for (auto& sphere : sphereList) {
			sphere.Render(shader, matrixStack.GetMatrix());
		}*/

		int index = 0;
		for (auto& chainLink : chainLinkList) {
			if (index == 0) {
				glm::vec3 pos = chainLinkIn.GetPosition();
				printf("Pos: (%4.2f, %4.2f, %4.2f) \n", pos.x, pos.y, pos.z);
			}
			chainLink.Render(shader, matrixStack.GetMatrix());
		}

		matrixStack.PopMatrix();
	}
}