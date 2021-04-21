#include "window.h"

// TODO: should probably add error checking here.
window::window(const std::string& title, uint32_t width, uint32_t height) : m_title(title), m_width(width), m_height(height) {
    glfwInit();
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

window::~window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void window::on_update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}