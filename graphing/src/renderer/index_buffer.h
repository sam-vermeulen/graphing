#pragma once

#include <cstdint>

class index_buffer {
public:
    index_buffer(uint32_t* indices, uint32_t count);
    ~index_buffer();

    void bind() const;
    void unbind() const;

    uint32_t get_count() const;

private:
    uint32_t m_id;
    uint32_t m_count;
};