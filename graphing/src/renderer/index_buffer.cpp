#include "index_buffer.h"

#include <glad/glad.h>

index_buffer::index_buffer(uint32_t* indices, uint32_t count) : m_count(count) {
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

index_buffer::~index_buffer() {
    glDeleteBuffers(1, &m_id);
}

void index_buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void index_buffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t index_buffer::get_count() const {
    return m_count;
}