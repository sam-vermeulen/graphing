#include "shader.h"

#include <array>

#include "util/logger.h"

shader::shader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source) : m_name(name) {
    std::unordered_map<GLenum, std::string> sources;

    sources[GL_VERTEX_SHADER] = vertex_source;
    sources[GL_FRAGMENT_SHADER] = fragment_source;

    compile(sources);
}

shader::shader(const std::string& name, const std::string& source_path) : m_name(name) {
    std::unordered_map<GLenum, std::string> sources;

    // LOAD SOURCES FROM FILE PATH

    compile(sources);
}

shader::~shader() {
    glDeleteProgram(m_id);
}

void shader::bind() const {
    glUseProgram(m_id);
}

void shader::unbind() const {
    glUseProgram(0);
}

void shader::set_bool(const std::string& name, bool val) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)val);
}

void shader::set_int(const std::string& name, int val) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), val);
}

void shader::set_float(const std::string& name, float val) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), val);
}

void shader::set_mat4f(const std::string& name, glm::mat4 val) const {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &val[0][0]);
}

void shader::compile(const std::unordered_map<GLenum, std::string>& sources) {
    GLuint program = glCreateProgram();
    std::array<GLenum, 2> glShaderIds;
    int glShaderIDIndex = 0;
    for (auto& i : sources) {
        GLenum type = i.first;
        const std::string& src = i.second;
        GLuint shader = glCreateShader(type);
        const GLchar* srcCStr = src.c_str();
        glShaderSource(shader,  1, &srcCStr, 0);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            LOG_WARN(infoLog.data());

            glDeleteShader(shader);
            break;
        }

        glAttachShader(program, shader);
        glShaderIds[glShaderIDIndex++] = shader;
    }

    m_id = program;

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        // PRINT ERROR HERE
        glDeleteProgram(program);

        for (auto id : glShaderIds) {
            glDeleteShader(id);
        }

        return;
    }

    for (auto id : glShaderIds) {
        glDetachShader(program, id);
        glDeleteShader(id);
    }
}