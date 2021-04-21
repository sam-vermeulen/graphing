#pragma once

#include <unordered_map>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class shader {
public:
    // source inline
    shader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);
    // source from file
    shader(const std::string& name, const std::string& source_path);
    ~shader();

    void bind() const;
    void unbind() const;

    // set uniforms
    void set_bool(const std::string& name, bool val) const;
    void set_int(const std::string& name, int val) const;
    void set_float(const std::string& name, float val) const;
    void set_mat4f(const std::string& name, glm::mat4 val) const;

    const std::string& get_name() const { return m_name; }

private:
    // create shader program, compiles shaders, links program, then deletes shaders.
    void compile(const std::unordered_map<GLenum, std::string>& sources);

    uint32_t m_id;
    std::string m_name;
};