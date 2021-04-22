#include "vertex_array.h"

#include <glad/glad.h>

vertex_array::vertex_array() {
    glCreateVertexArrays(1, &m_id);
}

vertex_array::~vertex_array() {
    glDeleteVertexArrays(1, &m_id);
}

void vertex_array::bind() const {
    glBindVertexArray(m_id);
}

void vertex_array::unbind() const {
    glBindVertexArray(0);
}

void vertex_array::add_vbo(const std::shared_ptr<vertex_buffer>& vbo) {
    bind();
    vbo->bind();
    m_vbos.push_back(vbo);

    uint16_t stride = 0;
    for (const buffer_element& element : vbo->get_layout()) {
        stride += data_type_size(element.type);
    }

    uint16_t index = 0;
    uint16_t offset = 0;
    for (const buffer_element& element : vbo->get_layout()) {
        glVertexAttribPointer(index, data_type_component_count(element.type), data_type_gl_enum(element.type), GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(index);
        offset += data_type_size(element.type);
        index++;
    }
}

void vertex_array::add_ibo(const std::shared_ptr<index_buffer>& ibo) {
    bind();
    ibo->bind();
    m_ibo = ibo;

}
