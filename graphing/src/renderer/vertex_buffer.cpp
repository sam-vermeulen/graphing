#include "vertex_buffer.h"

#include <glad/glad.h>

vertex_buffer::vertex_buffer(uint32_t size) {
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}

vertex_buffer::vertex_buffer(float* vertices, uint32_t size) {
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

vertex_buffer::~vertex_buffer() {
    glDeleteBuffers(1, &m_id);
}

void vertex_buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void vertex_buffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertex_buffer::set_data(const void* data, uint32_t size) const {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}