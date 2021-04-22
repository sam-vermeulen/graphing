#include "input.h"
#include "application.h"

#include <GLFW/glfw3.h>

bool input::is_mouse_button_pressed(const uint16_t button) {
    auto state = glfwGetMouseButton(application::get().get_window().get_handle(), button);
    return state == GLFW_PRESS;
}

bool input::is_key_pressed(const uint16_t key) {
    auto state = glfwGetKey(application::get().get_window().get_handle(), key);
    return state == GLFW_PRESS;
}

float input::get_mouse_x() {
    double xpos, ypos;
    glfwGetCursorPos(application::get().get_window().get_handle(), &xpos, &ypos);
    return (float)xpos;
}

float input::get_mouse_y() {
    double xpos, ypos;
    glfwGetCursorPos(application::get().get_window().get_handle(), &xpos, &ypos);
    return (float)ypos;
}

void input::get_mouse_pos(float* xpos, float* ypos) {
    glfwGetCursorPos(application::get().get_window().get_handle(), (double*)xpos, (double*)ypos);
}
