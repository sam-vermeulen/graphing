#include "core/entry.h"
#include "core/application.h"

#include "renderer/vertex_array.h"
#include "renderer/vertex_buffer.h"
#include "renderer/shader.h"

#include <memory>

const char* vertexSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec4 aColor;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos, 1.0f);\n"
    "color = aColor;"
    "}\0";

const char* fragmentSource = "#version 330 core\n"
    "in vec4 color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = color;\n"
    "}\0";

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
};

class app : public application {
public:
    app()
    {
        LOG_INFO("THIS IS IN THE APP");

        basic_shader = new shader("basic", vertexSource, fragmentSource);
        vbo = std::make_shared<vertex_buffer>(vertices, sizeof(vertices));
        vbo->set_layout({
            { data_type::float3, "aPos" },
            { data_type::float4, "aColor" }
        });
        vao.add_vbo(vbo);
        
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