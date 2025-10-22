#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// abstracts a GLFW + IMGUI graphic window 
/// </summary>
class Window {

private:
	const char* title;
	int width;
	int height;
	bool resizeDirty;
	GLFWwindow* window;

	void Resize(int width, int height);

public:
	Window(const char* title, int width, int height);

	bool Create();
	inline GLFWwindow* GetWindowPtr() const { return window; }

	void SetFramebufferCallback(GLFWframebuffersizefun callback);
	void SetMouseButtonCallback(GLFWmousebuttonfun callback);
	void SetCursorPosCallback(GLFWcursorposfun callback);
	void SetSetScrollCallback(GLFWscrollfun callback);
	void SetKeyboardCallback(GLFWkeyfun callback);

	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };
	inline const char* GetTitle() const { return title; };

	void SwapBuffers();
	void PollEvents();
	bool IsOpen();
	void ShouldClose();
	void Close();

	static void WindowResizeCallback(GLFWwindow* glfwWindow, int width, int height);
	inline bool ResizeDirty() const { return resizeDirty; };
};

