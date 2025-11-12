#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace Mouse {

	// mouse button states
	// indices: 
	//   - 0 : left 
	//   - 1 : right
	//   - 2 : center
	__declspec(selectany) bool mouse_buttons[] = { false, false, false };

	// new and previous position of the mouse cursor
	// indices: 
	//   - 0,1 : x,y of the new position; 
	//   - 2,3 - x,y of the previous position
	__declspec(selectany) float mouse_pos[] = { 0,0,0,0 }; // 0,1 - aktuelle Position, 2,3 - letzte Position

	// scroll wheel 
	// has the mouse wheel been rolled?
	__declspec(selectany) bool hasScrolled = true;
	// initial mouse wheel scroll value
	__declspec(selectany) float scrollValue = 0;

	////////////////////////////////////////////////////////////////////////////////////
	// code for the callbacks that are used by GLFW, never call from user code
	// /////////////////////////////////////////////////////////////////////////////////
	// was the mouse cursor moved for the first time?
	__declspec(selectany) bool firstMouseMove = true;
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}


