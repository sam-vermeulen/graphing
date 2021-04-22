#pragma once

enum class event_type {
    none = 0,
    window_close, window_resize, window_move, window_focus, window_lose_focus,
    key_pressed, key_released, key_typed,
    mouse_pressed, mouse_released, mouse_moved, mouse_scrolled
};

#define EVENT_TYPE(t) virtual bool operator==(event_type type) const override { return type == event_type::t; }\
                      static event_type static_type() { return event_type::t; }

class event {
public:
    virtual ~event() = default;

    virtual bool operator==(event_type type) const = 0;
};