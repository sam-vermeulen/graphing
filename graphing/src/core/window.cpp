#include "window.h"

#include "events/mouse_event.h"

// TODO: should probably add error checking here.
window::window(const std::string& title, uint32_t width, uint32_t height) {
    glfwInit();
    
    m_data.title = title;
    m_data.width = width;
    m_data.height = height;

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    initialize_callbacks();
}

void window::initialize_callbacks() {
    glfwSetWindowUserPointer(m_window, &m_data);

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        mouse_moved_event event((float)x, (float)y);
        data.eventCallback(event);        
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        switch(action) {
            case GLFW_PRESS:
            {
                mouse_pressed_event event(button);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                mouse_released_event event(button);
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x, double y) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        mouse_scrolled_event event((float)x, (float)y);
        data.eventCallback(event);
    });
}

window::~window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void window::on_update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}