#pragma once

#include "event.h"

class mouse_moved_event : public event {
public:
    mouse_moved_event(const float x, const float y) : m_x(x), m_y(y) {}

    EVENT_TYPE(mouse_moved)

    float get_x() const { return m_x; }
    float get_y() const { return m_y; }

private:
    float m_x, m_y;
};

class mouse_pressed_event : public event {
public:
    mouse_pressed_event(const uint16_t button_id) : m_button_id(button_id) { }

    EVENT_TYPE(mouse_pressed)

    uint16_t get_button_id() { return m_button_id; }

private:
    uint16_t m_button_id;
};

class mouse_released_event : public event {
public:
    mouse_released_event(const uint16_t button_id) : m_button_id(button_id) { }

    EVENT_TYPE(mouse_released)

    uint16_t get_button_id() { return m_button_id; }

private:
    uint16_t m_button_id;
};

class mouse_scrolled_event : public event {
public:
    mouse_scrolled_event(const float x, const float y) : m_x(x), m_y(y) { }

    EVENT_TYPE(mouse_scrolled)

    float get_x() { return m_x; }
    float get_y() { return m_y; }

private:
    float m_x;
    float m_y;
};