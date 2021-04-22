#pragma once

#include <cstdint>

#include <initializer_list>
#include <vector>
#include <string>

#include <glad/glad.h>

enum class data_type {
    none = 0, float1, float2, float3, float4, mat3, mat4, int1, int2, int3, int4
};

static GLenum data_type_gl_enum(data_type type) {
    switch(type) {
        case data_type::float1:
        case data_type::float2:
        case data_type::float3:
        case data_type::float4:
        case data_type::mat3:
        case data_type::mat4:
            return GL_FLOAT;
        case data_type::int1:
        case data_type::int2:
        case data_type::int3:
        case data_type::int4:
            return GL_INT;
    }
}

static uint16_t data_type_size(data_type type) {
    switch(type) {
        case data_type::float1: return sizeof(GLfloat);
        case data_type::float2: return sizeof(GLfloat) * 2;
        case data_type::float3: return sizeof(GLfloat) * 3;
        case data_type::float4: return sizeof(GLfloat) * 4;
        case data_type::mat3: return sizeof(GLfloat) * 3 * 3;
        case data_type::mat4: return sizeof(GLfloat) * 4 * 4;
        case data_type::int1: return sizeof(GLint);
        case data_type::int2: return sizeof(GLint) * 2;
        case data_type::int3: return sizeof(GLint) * 3;
        case data_type::int4: return sizeof(GLint) * 4;
    }
}

static uint16_t data_type_component_count(data_type type) {
    switch(type) {
        case data_type::float1: case data_type::int1: return 1;
        case data_type::float2: case data_type::int2: return 2;
        case data_type::float3: case data_type::int3: return 3;
        case data_type::float4: case data_type::int4: return 4;
        case data_type::mat3: return 9;
        case data_type::mat4: return 12;
    }
}

struct buffer_element {
    data_type type;
    std::string name;

    buffer_element(data_type type, const std::string& name) : type(type), name(name) {}
};

class vertex_buffer {
public:
    vertex_buffer(uint32_t size);
    vertex_buffer(float* vertices, uint32_t size);
    ~vertex_buffer();

    void set_layout(std::initializer_list<buffer_element> layout);
    const std::vector<buffer_element>& get_layout() const { return m_layout; }

    void bind() const;
    void unbind() const;

    void set_data(const void* data, uint32_t size) const;
private:
    std::vector<buffer_element> m_layout;
    uint32_t m_id;
};