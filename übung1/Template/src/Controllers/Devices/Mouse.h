#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace Mouse {
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	__declspec(selectany) bool mouse_buttons[] = { false, false, false };	// 0 - links, 1 - rechts, 2 - mitte
	__declspec(selectany) float mouse_pos[] = { 0,0,0,0 }; // 0,1 - aktuelle Position, 2,3 - letzte Position
	__declspec(selectany) bool firstMouseMove = true;
	__declspec(selectany) float scrollValue = 22.5f;
	__declspec(selectany) bool hasScrolled = true;
}


