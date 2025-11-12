#pragma once
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <GLFW/glfw3.h>

// analog input button values                   //      PS      |       XBOX
#define GLFW_JOYSTICK_BTN_DOWN 0                //  X           |   A
#define GLFW_JOYSTICK_BTN_RIGHT 1               //  Circle      |   B
#define GLFW_JOYSTICK_BTN_LEFT 2                //  Square      |   X
#define GLFW_JOYSTICK_BTN_UP 3                  //  Triangle    |   Y  
#define GLFW_JOYSTICK_SHOULDER_LEFT 4           //  L1          |   LB
#define GLFW_JOYSTICK_SHOULDER_RIGHT 5          //  R1          |   RB
#define GLFW_JOYSTICK_SELECT 6                  //  Share       |   Address
#define GLFW_JOYSTICK_START 7                   //  Options     |   Menu
#define GLFW_JOYSTICK_TRIGGER_LEFT 8            //  L2          |   LT			not working
#define GLFW_JOYSTICK_TRIGGER_RIGHT 9           //  R2          |   RT			not working
#define GLFW_JOYSTICK_DPAD_UP 10                //  Dpad up     |   Dpad up
#define GLFW_JOYSTICK_DPAD_RIGHT 11             //  Dpad right  |   Dpad right
#define GLFW_JOYSTICK_DPAD_DOWN 12              //  Dpad down   |   Dpad down
#define GLFW_JOYSTICK_DPAD_LEFT 13              //  Dpad left   |   Dpad left
#define GLFW_JOYSTICK_LEFT_STICK 14             //  L3          |   LS			not working
#define GLFW_JOYSTICK_RIGHT_STICK 15            //  R3          |   RS			not working
#define GLFW_JOYSTICK_HOME 16                   //  Home        |   Home		not working
#define GLFW_JOYSTICK_CLICK 17                  //  Touch pad   |   n/a			not working

// axes
#define GLFW_JOYSTICK_AXES_LEFT_STICK_X 0
#define GLFW_JOYSTICK_AXES_LEFT_STICK_Y 1
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_X 2
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_Y 3
#define GLFW_JOYSTICK_AXES_LEFT_TRIGGER 4
#define GLFW_JOYSTICK_AXES_RIGHT_TRIGGER 5


class Joystick
{
public:
	Joystick(int i);

	void update();

	float axesState(int axis);
	unsigned char buttonState(int button);

	int getAxesCount();
	int getButtonCount();

	bool isPresent();
	const char* getName();
	static int getID(int i);

private:
	int present;
	int id;
	const char* name;
	int axesCount;
	const float* axes;
	int buttonCount;
	const unsigned char* buttons;
};
#endif

