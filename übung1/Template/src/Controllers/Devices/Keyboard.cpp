#include "Controllers/Devices/Keyboard.h"

bool KeyBoard::keys[GLFW_KEY_LAST] = { false };
bool KeyBoard::keysPressed[GLFW_KEY_LAST] = { false };

void KeyBoard::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE) {
		if (!keys[key]) {
			keys[key] = true;
		}
	}
	else {
		keys[key] = false;
	}

	keysPressed[key] = action != GLFW_REPEAT;
}

bool KeyBoard::key(int key)
{
	return keys[key];
}

bool KeyBoard::keyChanged(int key)
{
	bool tmp = keysPressed[key];
	keysPressed[key] = false;
	return tmp;
}

bool KeyBoard::keyWentUp(int key)
{
	return !keys[key] && keyChanged(key);
}

bool KeyBoard::keyWentDown(int key)
{
	return keys[key] && keyChanged(key);
}
