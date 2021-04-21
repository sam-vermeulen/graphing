#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class window {
public:
    window(const std::string& title, uint32_t width, uint32_t height);
    ~window();

    void on_update();

    GLFWwindow* get_handle() const { return m_window; };
    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }

private:
    std::string m_title;
    uint32_t m_width, m_height;

    GLFWwindow* m_window;

};