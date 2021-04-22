#include "core/entry.h"
#include "core/application.h"

#include "renderer/vertex_array.h"
#include "renderer/vertex_buffer.h"
#include "renderer/shader.h"

#include <memory>

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
    "FragColor = vec4(0.95f, 0.95f, 0.58f, 1.0f);\n"
    "}\0";

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f, 0.5f, 0.0f
};

class app : public application {
public:
    app()
    {
        LOG_INFO("THIS IS IN THE APP");

        basic_shader = new shader("basic", vertexSource, fragmentSource);
        vbo = std::make_shared<vertex_buffer>(vertices, sizeof(vertices));
        vao.add_vbo(vbo);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
    }

    void on_update() override {
        glClear(GL_COLOR_BUFFER_BIT);

        basic_shader->bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    vertex_array vao;
    std::shared_ptr<vertex_buffer> vbo;
    shader* basic_shader;

};

application* create_application() {
    return new app();
}