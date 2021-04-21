#pragma once

#include <memory>
#include <vector>

#include "vertex_buffer.h"
#include "index_buffer.h"

class vertex_array {
public:
    vertex_array();
    ~vertex_array();

    void bind() const;
    void unbind() const;

    void add_vbo(const std::shared_ptr<vertex_buffer>& vbo);
    void add_ibo(const std::shared_ptr<index_buffer>& ibo);

    const std::vector<std::shared_ptr<vertex_buffer>>& get_vbos() const { return m_vbos; }
    const std::shared_ptr<index_buffer>& get_ibo() const { return m_ibo; }
private:
    uint32_t m_id;
    std::vector<std::shared_ptr<vertex_buffer>> m_vbos;
    std::shared_ptr<index_buffer> m_ibo;
    
};