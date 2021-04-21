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
}

void vertex_array::add_ibo(const std::shared_ptr<index_buffer>& ibo) {
    bind();
    ibo->bind();
    m_ibo = ibo;

}