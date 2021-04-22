#pragma once

#include "event.h"

class window_close_event : public event {
public:
    window_close_event() {}

    EVENT_TYPE(window_close)
};

class window_resize_event : public event {
public:
    window_resize_event(int width, int height) : m_width(width), m_height(height) {}

    EVENT_TYPE(window_resize)
private:
    int m_width;
    int m_height;
};

class window_move_event : public event {
public:
    window_move_event(int width, int height) : m_width(width), m_height(height) {}

    EVENT_TYPE(window_move)
private:
    int m_width;
    int m_height;
};

class window_focus_event : public event {
public:
    window_focus_event() {}

    EVENT_TYPE(window_focus)
};

class window_lose_focus_event : public event {
public:
    window_lose_focus_event() {}

    EVENT_TYPE(window_lose_focus)
};