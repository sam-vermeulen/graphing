#include "window.h"

#include "events/mouse_event.h"
#include "events/key_event.h"
#include "events/window_event.h"

// TODO: should probably add error checking here.
window::window(const std::string& title, uint32_t width, uint32_t height) {
    glfwInit();
    
    m_data.title = title;
    m_data.width = width;
    m_data.height = height;

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    glfwSetWindowUserPointer(m_window, &m_data);

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        window_close_event event;
        data.eventCallback(event);
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        data.width = width;
        data.height = height;

        window_resize_event event(width, height);
        data.eventCallback(event);
    });

    glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        window_move_event event(x, y);
        data.eventCallback(event);
    });

    glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        if (focused) {
            window_focus_event event;
            data.eventCallback(event);
        } else {
            window_lose_focus_event event;
            data.eventCallback(event);
        }
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

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        switch(action) {
            case GLFW_PRESS:
            {
                key_pressed_event event(key, 0);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                key_released_event event(key);
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                key_pressed_event event(key, 1);
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode) {
        window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

        key_typed_event event(keycode);
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