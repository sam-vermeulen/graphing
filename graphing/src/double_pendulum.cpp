#include "core/entry.h"
#include "core/application.h"
#include "core/input.h"

#include "renderer/vertex_array.h"
#include "renderer/vertex_buffer.h"
#include "renderer/shader.h"

#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

#include <utility>

constexpr auto PI = 3.14159263;

const char* vertexSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec4 aColor;\n"
    "out vec4 color;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * vec4(aPos, 1.0f);\n"
    "color = aColor;"
    "}\0";

const char* fragmentSource = "#version 330 core\n"
    "in vec4 color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = color;\n"
    "}\0";

struct line {
    glm::vec3 start;
    glm::vec4 color_a;
    glm::vec3 end;
    glm::vec4 color_b;
};

class line_renderer {
public:
    line_renderer() {
        vao = std::make_unique<vertex_array>();
        vbo = std::make_shared<vertex_buffer>(maxLines * sizeof(line));
        vbo->set_layout({
            { data_type::float3, "aPos" },
            { data_type::float4, "aColor" }
        });
        vao->add_vbo(vbo);
        linesBase = new line[maxLines];
        lineShader = std::make_unique<shader>("line shader", vertexSource, fragmentSource);
    }

    void begin_scene() {

        lineShader->bind();
        lineShader->set_mat4f("projection", glm::ortho(0.0f, 100.0f, 0.0f, 100.0f));
        lineCount = 0;
        linesPtr = linesBase;
    }

    void draw_line(line& l) {
        if (lineCount + 1 > maxLines) {
            LOG_WARN("Max line ({0}) reached cannot draw more lines.", maxLines);
            return; 
        }

        linesPtr->start = l.start;
        linesPtr->end = l.end;
        linesPtr->color_a = l.color_a;
        linesPtr->color_b = l.color_b;
        linesPtr++;

        lineCount++;
    }

    void end_scene() {
        uint32_t size = (uint32_t)((uint8_t*)linesPtr - (uint8_t*)linesBase);
        vbo->set_data(linesBase, size);
        glDrawArrays(GL_LINES, 0, lineCount * 2);
    }
private:
    uint32_t maxLines = 2000000;
    uint32_t lineCount = 0;

    std::unique_ptr<vertex_array> vao;
    std::shared_ptr<vertex_buffer> vbo;
    std::unique_ptr<shader> lineShader;

    line* linesBase = nullptr;
    line* linesPtr = nullptr;
};

const glm::vec4 black = {0.0f, 0.0f, 0.0f, 1.0f};

class double_pendulum {
public:
    double_pendulum(float gravity, float l1, float l2, float m1, float m2, float a1, float a2, glm::vec4 color_a, glm::vec4 color_b, glm::vec4 color_c)
        : m_gravity(gravity), m_l1(l1), m_l2(l2), m_m1(m1), m_m2(m2), m_a1(a1), m_a2(a2), m_color_a(color_a), m_color_b(color_b), m_color_c(color_c) {
        m_pos1 = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pos2 = glm::vec3(0.0f, 0.0f, 0.0f);
        m_vel1 = 0.0f;
        m_vel2 = 0.0f;
        m_acc1 = 0.0f;
        m_acc2 = 0.0f;

        line_a.start = glm::vec3(50.0f, 50.0f, 0.0f);

        line_a.color_a = color_a;
        line_a.color_b = color_b;
        line_b.color_a = color_b;
        line_b.color_b = color_c;
    }

    void update() {
        m_pos1 = { 50.0f + m_l1 * glm::sin(m_a1), 50.0f + m_l1 * glm::cos(m_a1), 0.0f };
        m_pos2 = { m_pos1.x + m_l2 * glm::sin(m_a2), m_pos1.y + m_l2 * glm::cos(m_a2), 0.0f };

        denominator = 2 * m_m1 + m_m2 - m_m2 * glm::cos(2 * m_a1 - 2 * m_a2);
        m_acc1 = -m_gravity * (2 * m_m1 + m_m2) * glm::sin(m_a1) - m_m1 * m_gravity * glm::sin(m_a1 - 2 * m_a2) - 2 * glm::sin(m_a1 - m_a2) * m_m2 * (m_vel2 * m_vel2 * m_l2 + m_vel1 * m_vel1 * m_l1 * glm::cos(m_a1 - m_a2));
        m_acc1 = m_acc1 / (m_l1 * denominator);
        m_acc2 = 2 * glm::sin(m_a1 - m_a2) * (m_vel1 * m_vel1 * m_l1 * (m_m1 + m_m2) + m_gravity * (m_m1 + m_m2) * glm::cos(m_a1) + m_vel2 * m_vel2 * m_l2 * m_m2 * glm::cos(m_a1 - m_a2));
        m_acc2 = m_acc2 / (m_l2 * denominator);

        m_vel1 += m_acc1;
        m_vel2 += m_acc2;
        m_a1 += m_vel1;
        m_a2 += m_vel2;

        m_vel1 *= 0.9983f;
        m_vel2 *= 0.9983f;
    }

    void draw(line_renderer& renderer) {
        line_a.end = m_pos1;
        line_b.start = m_pos1;
        line_b.end = m_pos2;

        renderer.draw_line(line_a);
        renderer.draw_line(line_b);
    }

private:
    line line_a, line_b;

    float m_gravity;
    float m_l1, m_l2;
    float m_m1, m_m2;
    float m_a1, m_a2;
    float m_acc1, m_acc2;
    float m_vel1, m_vel2;

    float denominator = 0.0f;
    glm::vec4 m_color_a;
    glm::vec4 m_color_b;
    glm::vec4 m_color_c;

    glm::vec3 m_pos1, m_pos2;
};

float interpolate(float startValue, float endValue, int stepNumber, int lastStepNumber)
{
    return (endValue - startValue) * stepNumber / lastStepNumber + startValue;
}

class app : public application {
public:
    app() {
        //glClearColor(0.82f, 0.93f, 0.99f, 1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                
        int count = 80000;

        for (int i = 0; i < count; i++) {
            glm::vec4 color_b(interpolate(0.8f, 0.5f, i, count), interpolate(0.8f, 0.3f, i, count), interpolate(0.2f, 0.3f, i, count), 0.05f);
            glm::vec4 color_a(interpolate(0.4f, 0.5f, i, count), interpolate(1.0f, 0.2f, i, count), interpolate(0.8f, 0.3f, i, count), 0.05f);
            glm::vec4 color_c(interpolate(1.0f, 0.3f, i, count), interpolate(0.3f, 0.2f, i, count), interpolate(0.4f, 0.8f, i, count), 0.05f);
            dp.push_back(std::make_unique<double_pendulum>(-0.1f, 20.0f, 20.0f, 1000.0f, 500.0f, (i + 1)*0.0000001f, 0, color_a, color_b, color_c));
            //dp.push_back(std::make_unique<double_pendulum>(-0.1f, 20.0f, 20.0f, 5.0f, 5.0f, (i + 1) * 0.0000001f, 0, color_a, color_b, color_c));
        }
    }

    void on_update() override {

        glClear(GL_COLOR_BUFFER_BIT);

        if (input::is_key_pressed(GLFW_KEY_SPACE)) {
            m_begin = true;
        }

        if (m_begin) {
            renderer.begin_scene();
            for (std::unique_ptr<double_pendulum>& a : dp) {
                a->update();
                a->draw(renderer);
            }
            renderer.end_scene();
        }
    }

private:
    std::vector<std::unique_ptr<double_pendulum>> dp;
    line_renderer renderer;

    bool m_begin = false;
};

application* create_application() {
    return new app();
}