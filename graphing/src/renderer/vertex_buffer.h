#pragma once

#include <cstdint>

class vertex_buffer {
public:
    vertex_buffer(uint32_t size);
    vertex_buffer(float* vertices, uint32_t size);
    ~vertex_buffer();

    void bind() const;
    void unbind() const;

    void set_data(const void* data, uint32_t size) const;
private:
    uint32_t m_id;
};