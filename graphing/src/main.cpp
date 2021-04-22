#include <cstdio>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/logger.h"

#include "renderer/vertex_array.h"
#include "renderer/vertex_buffer.h"
#include "renderer/shader.h"
#include "core/window.h"

#include "events/event.h"
#include "events/mouse_event.h"

#include "events/event_handler.h"

const char* vertexSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos, 1.0f);\n"
    "}\0";

const char* fragmentSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\0";

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

void on_mouse_move(mouse_moved_event& e) {
    LOG_INFO("Mouse moved: {0}, {1}", e.get_x(), e.get_y());
}


void on_event(event& e) {
    event_handler handler(e);
    handler.handle<mouse_moved_event>(on_mouse_move);
}

int main() {
    logger::init();

    window window("hello", 500, 500);
    window.set_event_callback(on_event);

    shader basic_shader("basic", vertexSource, fragmentSource);
    vertex_array vao;
    vertex_buffer vbo(vertices, sizeof(vertices));
    vao.add_vbo(std::make_shared<vertex_buffer>(vbo));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
    while (!glfwWindowShouldClose(window.get_handle())) {
        glClear(GL_COLOR_BUFFER_BIT);

        basic_shader.bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.on_update();
    }

    return 0;
}