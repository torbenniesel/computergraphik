#include "Controllers/Devices/Mouse.h"

/////////////////////////////////////////////////////////////////////////////////
//	Mouse Button CALLBACK Function
//		button - which mouse button was pressed or released
/////////////////////////////////////////////////////////////////////////////////

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        mouse_buttons[button] = true;
    }
    else {
        mouse_buttons[button] = false;
    }
    //std::cout << mouse_buttons[0] << mouse_buttons[1] << mouse_buttons[2] << std::endl;
}

void Mouse::mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouseMove) {
        mouse_pos[0] = (float)xpos;
        mouse_pos[1] = (float)ypos;
        firstMouseMove = false;
    }
    mouse_pos[2] = mouse_pos[0];
    mouse_pos[3] = mouse_pos[1];
    mouse_pos[0] = (float)xpos;
    mouse_pos[1] = (float)ypos;
    //std::cout << mouse_pos[0] << " " << mouse_pos[1] << " " << mouse_pos[2] << " " << mouse_pos[3] << std::endl;
}

void Mouse::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    hasScrolled = true;
    scrollValue -= (float)yoffset;
    if (scrollValue < 1.0f)
        scrollValue = 1.0f;
    if (scrollValue > 100.0f)
        scrollValue = 100.0f;
    //std::cout << scrollValue << std::endl;
}
