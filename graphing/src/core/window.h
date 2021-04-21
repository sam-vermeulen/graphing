#pragma once

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "events/event.h"

class window {
public:
    window(const std::string& title, uint32_t width, uint32_t height);
    ~window();
    using event_callback_type = std::function<void(event&)>;

    void on_update();

    GLFWwindow* get_handle() const { return m_window; }
    uint32_t get_width() const { return m_data.width; }
    uint32_t get_height() const { return m_data.height; }

    void set_event_callback(const event_callback_type& callback) { m_data.eventCallback = callback; }

private:
    GLFWwindow* m_window;

    void initialize_callbacks();

    struct window_data { 
        std::string title;
        uint32_t width, height;
        event_callback_type eventCallback;
    };

    window_data m_data;
};