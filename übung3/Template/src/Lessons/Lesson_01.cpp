#include "Lesson_01.h"

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
	Lesson1::Lesson1() :
		coordSystem(-10, 10, -10, 10, -10, 10),
		wireframeOn(false),
		ambLightOn(false),
		dirLightOn(false),

		cPosDiff(0),
		cCenterDiff(0),
		cUpDiff(0),

		camera(),
		orbitCamera(),
		useOrbitalCamera(true),

		lastScrollValue(0),

		xAnimation(false),
		yAnimation(false),
		animationSpeed(0.5f)
	{
		// enable the rendering of the coordinate system
		coordSystem.Enable(true);

		// select the common shader
		shader = Shader("res/shaders/object.shader");

		// init lamps
		SetupLights();

		// init the cube model, use wood texture
		cube = Cube(6.0f, { "res/textures/wood.jpg" }, { aiTextureType_DIFFUSE }, glm::vec3(0, 0, 0), glm::vec3(0.1f));

		// TODO U03.4: 
		// define the geometry by calling the constructors 
		// and append it to the collection of models
		// ...
		InitSnowman(glm::vec3(0, 1.0f, 0));

		Cylinder c = Cylinder(1, 1, 4, Material::black_plastic, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));

	}

	void Lesson1::InitSnowman(glm::vec3 origin = glm::vec3(0, 1.0f, 0)) {
		int stacks = 30;
		int slices = 30;
		Material snowMat = Material::white_plastic;

		const glm::vec3 rotation = glm::vec3(0);	//don't change
		const glm::vec3 scale = glm::vec3(1.0f);	//don't change

		float bRadius = 0.1f;
		glm::vec3 buttonScale = scale * glm::vec3(1.0f, 1.0f, 0.5f);
		Material blackPlastic = Material::black_plastic;

		//Body
		float s1Radius = 2.0f;
		float s2Radius = 1.5f;
		float s3Radius = 1.0f;
		float offset = 0.25f;
		glm::vec3 s1Pos = origin + glm::vec3(0, 0, 0);
		glm::vec3 s2Pos = glm::vec3(0, s1Pos.y + s1Radius + s2Radius - s2Radius * offset, 0);
		glm::vec3 s3Pos = glm::vec3(0, s2Pos.y + s2Radius + s3Radius - s3Radius * offset, 0);

		snowMan.push_back(Sphere(s1Radius, stacks, slices, snowMat, s1Pos, scale, rotation));
		snowMan.push_back(Sphere(s2Radius, stacks, slices, snowMat, s2Pos, scale, rotation));
		snowMan.push_back(Sphere(s3Radius, stacks, slices, snowMat, s3Pos, scale, rotation));

		//Body Buttons
		double degStart = 35 * M_PI / 180;
		double degStep = 20 * M_PI / 180;
		glm::vec3 b1Pos = s2Pos + glm::vec3(0, glm::sin(degStart), glm::cos(degStart)) * s2Radius;

		glm::vec3 b2Pos = s2Pos + glm::vec3(0, glm::sin(degStart - degStep), glm::cos(degStart - degStep)) * s2Radius;
		glm::vec3 b3Pos = s2Pos + glm::vec3(0, glm::sin(degStart - 2 * degStep), glm::cos(degStart - 2 * degStep)) * s2Radius;

		snowMan.push_back(Sphere(bRadius, stacks, slices, blackPlastic, b1Pos, buttonScale, rotation));
		snowMan.push_back(Sphere(bRadius, stacks, slices, blackPlastic, b2Pos, buttonScale, rotation));
		snowMan.push_back(Sphere(bRadius, stacks, slices, blackPlastic, b3Pos, buttonScale, rotation));

		//Eye Buttons
		double degEyesUp = 20 * M_PI / 180;
		double degEyesLeft = 90 * M_PI / 180;
		double eyeY = glm::sin(degEyesUp);
		double eyeRadius = glm::cos(degEyesUp);
		double eyeLeftZ = glm::sin(degEyesLeft) * eyeRadius - 0.05f;
		double eyeLeftX = glm::cos(degEyesLeft) * eyeRadius;
		double eyeRightX = glm::cos(degEyesLeft - 20 * M_PI / 180) * eyeRadius;

		glm::vec3 eyeLeftPos = s3Pos + glm::vec3(0.3, eyeY, eyeLeftZ) * s3Radius;
		glm::vec3 eyeRightPos = s3Pos + glm::vec3(-0.3, eyeY, eyeLeftZ) * s3Radius;

		snowMan.push_back(Sphere(bRadius, stacks, slices, blackPlastic, eyeLeftPos, buttonScale, rotation));
		snowMan.push_back(Sphere(bRadius, stacks, slices, blackPlastic, eyeRightPos, buttonScale, rotation));

		//Nose
		glm::vec3 nosePos = s3Pos + glm::vec3(0, 0, 1) * s3Radius;
		float noseHeight = 0.4f;
		float noseRadius = 0.1f;
		snowMan.push_back(Cone(noseRadius, noseHeight, stacks, slices, Color::orange, nosePos, scale, rotation));

		//Mouse
		glm::vec3 mousePos = s3Pos + glm::vec3(0, glm::sin(-15 * M_PI / 180), glm::cos(-15 * M_PI / 180)) * s3Radius;
		mousePos.z = mousePos.z - 0.05f;
		glm::vec3 mouseScale = scale * glm::vec3(2.5f, 1.0f, 0.5f);
		snowMan.push_back(Sphere(0.1f, stacks, slices, blackPlastic, mousePos, mouseScale, rotation));

		//Hat
		glm::vec3 hatPos = s3Pos + glm::vec3(0, glm::sin(90 * M_PI / 180), glm::cos(90 * M_PI / 180)) * s3Radius * 0.75f;
		float hatBottomHeight = 0.1f;
		float hatBottomRadius = s3Radius * 1.1;
		float hatTopHeight = 1.4f;
		float hatTopRadius = s3Radius * 0.75;
		snowMan.push_back(Cylinder(hatBottomRadius, hatBottomHeight, slices, Material::black_plastic, hatPos, scale, rotation));
		snowMan.push_back(Cylinder(hatTopRadius, hatTopHeight, slices, Material::black_plastic, hatPos, scale, rotation));
	}

	

	// destructor: cleanup 
	Lesson1::~Lesson1() {
		cube.Cleanup();
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

		// render camera center
		if (useOrbitalCamera) {
			Sphere s = Sphere(0.2f, 20, 20, Material::gold,
				orbitCamera.GetCenter(), glm::vec3(1.0f), glm::vec3(0));
			s.Render(shader, matrixStack.GetMatrix());
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

		// Oribital camera movement
		// 
		if (useOrbitalCamera) {

			if (KeyBoard::key(GLFW_KEY_LEFT_CONTROL) && KeyBoard::key(GLFW_KEY_R)) {
				orbitCamera.SetCenter(glm::vec3(0));
			}

			// Catch Left-Control key
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
		}

		// the middle mouse button is pressed 
		// --> move the camera position to the left, right, up, down if STRG is not pressed
		// --> move the camera position forward or backward if STRG is pressed
		// --> move the center to the left, right, up, down if SHIFT is pressed
		// --> move the center forward / backward if SHIFT-CONTROL is pressed

		if (useOrbitalCamera && Mouse::mouse_buttons[2]) {
			glm::vec3 dir = glm::vec3(0);
			glm::vec3 dirMoveCenter = glm::vec3(0);

			

			float mouseX = Mouse::mouse_pos[0];
			float prevMouseX = lastMouseX ? lastMouseX : Mouse::mouse_pos[2];
			float mouseY = Mouse::mouse_pos[1];
			float prevMouseY = lastMouseY ? lastMouseY : Mouse::mouse_pos[3];
			float mouseXChange = mouseX - prevMouseX; 
			float mouseYChange = -(mouseY - prevMouseY); 

			// map 2d mouse movement to 3d vector
			if (KeyBoard::key(GLFW_KEY_LEFT_CONTROL)) { // move forward / backward 
				dir.z = mouseYChange; 
			}
			else { // orbit left / right , up / down
				dir.x = mouseXChange; 
				dir.y = mouseYChange; 
			}


			if (KeyBoard::key(GLFW_KEY_LEFT_SHIFT)) { 
				if (KeyBoard::key(GLFW_KEY_LEFT_CONTROL)) { // move center forward / backward
					dirMoveCenter.z = mouseYChange;
				}
				else { // move center left / right , up / down
					dirMoveCenter.x = mouseXChange;
					dirMoveCenter.y = mouseYChange;
				}

				orbitCamera.MoveCenter(dirMoveCenter, deltaTime);
			}
			else {
				orbitCamera.Move(dir, deltaTime);
			}

			dir.x = Mouse::mouse_pos[0] - Mouse::mouse_pos[2];
			// reversed Y since mouse (0,0) is in the top left corner of the window 
			dir.y = Mouse::mouse_pos[3] - Mouse::mouse_pos[1];
		}


		// Save last Mouse Pos
		lastMouseX = Mouse::mouse_pos[0];
		lastMouseY = Mouse::mouse_pos[1];


		// zooming with the mouse wheel:
		// modify the "focal lenght" of the camera  
		if (Mouse::hasScrolled) {
			Mouse::hasScrolled = false;
			float sv = Mouse::scrollValue - lastScrollValue;
			lastScrollValue = Mouse::scrollValue;

			if (useOrbitalCamera) {
				orbitCamera.AddFovy(sv);
				orbitCamera.UpdateProjection();
			}
			else {
				camera.AddFovy(sv);
				camera.UpdateProjection();
			}
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
		ImGui::NewLine();

		if (ImGui::RadioButton("Default cam", useOrbitalCamera == false)) {
			useOrbitalCamera = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("OrbitalCamera", useOrbitalCamera == true)) {
			useOrbitalCamera = true;
		}

		if (!useOrbitalCamera) {
			ImGui::DragFloat3("Position", &cPosDiff.x, 0.05f);
			ImGui::DragFloat3("Center", &cCenterDiff.x, 0.05f);
			ImGui::DragFloat3("Up", &cUpDiff.x, 0.05f);
		}
		else {
			ImGui::Text("Usage: ");
			ImGui::Text("  - cursor keys: move camera position left, right, up, down");
			ImGui::Text("  - PageUp, PageDown: move camera forward, backward");

			ImGui::Text("Animation: ");
			ImGui::SameLine(); ImGui::Checkbox("horicontal", &xAnimation);
			ImGui::SameLine(); ImGui::Checkbox("vertical", &yAnimation);
			ImGui::SliderFloat("Speed", &animationSpeed, -20.0f, 20.0f);

		}

	}

	// update the scene: 
	// implement your simulation/animation logic here
	void Lesson1::Simulation(double deltaTime)
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

		if (useOrbitalCamera) {
			glm::vec3 movement = glm::vec3(0);
			if (xAnimation) movement.x = -animationSpeed;
			if (yAnimation) movement.y = -animationSpeed;
			orbitCamera.Move(movement, deltaTime);
		}
	}

	// render one frame of your scene here
	// coord base = world coordinates
	// the camera has already been set in PrepareFrame()
	void Lesson1::Render()
	{
		cube.Render(shader, matrixStack.GetMatrix());

		DrawSnowman();
	}

	void Lesson1::DrawSnowman() {

		
		matrixStack.PushMatrix();
		{
			matrixStack.Translate(0, 0, 0);
			matrixStack.Rotate(0, 0, 0); // align snowman axis with world axis
			matrixStack.Scale(glm::vec3(0.5f));
			for (Model& m : snowMan)
			{
				m.Render(shader, matrixStack.GetMatrix());
			}
		}
		matrixStack.PopMatrix();
		


		// TODO U03.3: model and render a snowman
		// part 1: define the instances of the geometry by calling the constructors 
		// ...

		// part 2: render the geometry by calling <object>.Render(shader, matrixStack.GetMatrix())
		// ...

		// TODO U03.4: render the collection of geometrical objects
		// ...

	}
}