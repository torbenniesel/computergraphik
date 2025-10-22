#include "Window/Window.h"
#include "imgui/imgui.h"
#include <iostream>
#include <cassert>

Window::Window(const char* title, int width, int height) {
	assert(title != nullptr && width > 0 && height > 0);
	this->title = title;
	this->width = width;
	this->height = height;
	resizeDirty = true;
	window = nullptr;
}

bool Window::Create() {
	// init GLFW, create the window and make GLFW context current
	// init GLEW

	// init GLFW lib
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW..." << std::endl;
		return false;
	}

	// create a window with OpenGL context
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}

	// set the pointer to the window to access the correct resize callback
	glfwSetWindowUserPointer(window, this);

	// make the window's context current
	glfwMakeContextCurrent(window);

	// enable VSYNC
	glfwSwapInterval(1);

	// init GLEW
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to init GLEW..." << std::endl;
		glfwTerminate();
		return false;
	}

	// get GL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	resizeDirty = true;
	return true;
}

void Window::SetFramebufferCallback(GLFWframebuffersizefun callback) {
	// set the window resize callback
	glfwSetFramebufferSizeCallback(window, callback);
}

void Window::SetMouseButtonCallback(GLFWmousebuttonfun callback) {
	// set the mouse button callback
	glfwSetMouseButtonCallback(window, callback);
}
void Window::SetCursorPosCallback(GLFWcursorposfun callback) {
	// set the mouse movement callback
	glfwSetCursorPosCallback(window, callback);
}
void Window::SetSetScrollCallback(GLFWscrollfun callback) {
	// set the mouse wheel callback
	glfwSetScrollCallback(window, callback);
}
void Window::SetKeyboardCallback(GLFWkeyfun callback) {
	// set the keyboard callback
	glfwSetKeyCallback(window, callback);
}

void Window::WindowResizeCallback(GLFWwindow* glfwWindow, int width, int height)
{
	// called from GLFW when window was resized
	// is also called in case the window was minimized, so we need to ignore this
	if ((width < 1) || (height < 1)) return;

	auto window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->Resize(width, height);
}

void Window::Resize(int width, int height) {
	// resize to new dimensions
	if (width != this->width || height != this->height) {
		this->width = width;
		this->height = height;
		this->resizeDirty = true;
	}
};

void Window::SwapBuffers() {
	// show the rendered image
	glfwSwapBuffers(window);
}

void Window::PollEvents() {
	// poll for and process events
	glfwPollEvents();
}

bool Window::IsOpen() {
	// true if window should not close soon
	return !glfwWindowShouldClose(window);
}

void Window::ShouldClose() {
	// signal that window should close soon
	glfwSetWindowShouldClose(window, true);
}

void Window::Close() {
	// terminate GLFW and close the window
	glfwTerminate();
}

