#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

class KeyBoard
{

public:
	static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool key(int key);
	static bool keyChanged(int key);
	static bool keyWentUp(int key);
	static bool keyWentDown(int key);

private:
	static bool keys[];
	static bool keysPressed[];

};
#endif

