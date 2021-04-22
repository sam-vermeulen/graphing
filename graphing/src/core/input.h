#pragma once

#include <cinttypes>
#include <memory>

#include "core/window.h"

class input {
public:
    static bool is_key_pressed(uint16_t key);
    static bool is_mouse_button_pressed(uint16_t button);
    static float get_mouse_x();
    static float get_mouse_y();
    static void get_mouse_pos(float* xpos, float* ypos);
};