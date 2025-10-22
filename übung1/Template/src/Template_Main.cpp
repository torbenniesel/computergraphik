#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Tests/ClearColor.h"
#include "Lessons/Introduction.h"
#include "Lessons/Lesson_01.h"

#include "Controllers/Devices/Mouse.h"
#include "Controllers/Devices/Keyboard.h"
#include "Window/Window.h"

static const char* windowTitle = "PrakCG 2025";
static unsigned int windowWidth = 1024;
static unsigned int windowHeight = 768;

// the program entry point
int main(void) {
	// our graphics window
	Window window(windowTitle, windowWidth, windowHeight);

	// create a window with OpenGL context
	if (!window.Create()) {
		std::cout << "Failed to create a window..." << std::endl;
		return -1;
	}

	// assign the callbacks
	window.SetFramebufferCallback(Window::WindowResizeCallback);
	window.SetMouseButtonCallback(Mouse::mouse_button_callback);
	window.SetCursorPosCallback(Mouse::mouse_move_callback);
	window.SetSetScrollCallback(Mouse::mouse_scroll_callback);
	window.SetKeyboardCallback(KeyBoard::keyboard_callback);

	// we have a window, {}'s only for clarity
	{
		// init the GUI and bind it to the window
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window.GetWindowPtr(), false);
		ImGui::StyleColorsDark();

		// prepare the test selection menu
		PrakCG::Plugin* currentPlugin = nullptr;
		PrakCG::MenuEntries* Menu = new PrakCG::MenuEntries(currentPlugin);
		Menu->RegisterPlugin<PrakCG::TestClearColor>("Clear Color");
		Menu->RegisterPlugin<PrakCG::Introduction>("Introduction");
		Menu->RegisterPlugin<PrakCG::Lesson1>("Lesson 01");
		currentPlugin = new PrakCG::Lesson1;

		// init depth test to show our 3d scene properly
		glEnable(GL_DEPTH_TEST);

		// prepare the performance counter
		double deltaTime = 0;
		double lastTime = glfwGetTime();

		// loop until the user closes the window
		while (true == window.IsOpen()) {
			// the rendering of a frame starts here 

			// signal to the GUI that a new frame is starting
			ImGui_ImplGlfwGL3_NewFrame();

			// render the menu
			ImGui::Begin("Menu");
			if (currentPlugin != Menu && ImGui::Button("<-- Back to plugin selection")) {
				// change plugin
				delete currentPlugin;
				currentPlugin = Menu;
			}

			// render the selected test
			if (currentPlugin) {
				// get the duration of last frame
				double now = glfwGetTime();
				deltaTime = now - lastTime;
				lastTime = now;

				// Plugin: update the camera if the window was resized
				if (true == window.ResizeDirty()) {
					int w = window.GetWidth(); int h = window.GetHeight();
					glViewport(0, 0, w, h);
					currentPlugin->OnFrameBufferChanged(w, h);
				}

				// Plugin: update the model
				currentPlugin->OnUpdate(deltaTime);

				// Plugin: render the model
				currentPlugin->OnRender();

				// Plugin: render the GUI
				currentPlugin->OnImGuiRender();
			}

			// finish the GUI
			ImGui::End();
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			// show the rendered image
			window.SwapBuffers();

			// poll for and process events
			window.PollEvents();

			// ESC was pressed, exit the renderloop
			if (KeyBoard::key(GLFW_KEY_ESCAPE))
				window.ShouldClose();
		}
	}

	// shutdown IMGUI
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	// shutdown GLFW
	window.Close();

	// exit
	return 0;
}

