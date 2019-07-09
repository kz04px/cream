#include "shaders.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include "clog/clog.hpp"

namespace cream {

Shader::Shader() {
}

Shader::~Shader() {
    clog::Log::get()->info("Shader destroyed (", value_, ")");
    glDeleteShader(value_);
}

void Shader::load_text(const ShaderType &type, const std::string &text) {
    assert(type == ShaderType::VERTEX_SHADER || type == ShaderType::FRAGMENT_SHADER);

    switch (type) {
        case ShaderType::VERTEX_SHADER:
            value_ = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::FRAGMENT_SHADER:
            value_ = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            assert(false);
            break;
    }

    clog::Log::get()->info("Shader created (", value_, ")");

    const char *source = text.c_str();
    int length = text.size();
    type_ = type;
    glShaderSource(value_, 1, &source, &length);
    glCompileShader(value_);
}

void Shader::load_file(const ShaderType &type, const std::string &path) {
    assert(type == ShaderType::VERTEX_SHADER || type == ShaderType::FRAGMENT_SHADER);

    std::ifstream t(path);

    if (!t.is_open()) {
        clog::Log::get()->warn("Shader file ", path, " not found.");
        return;
    }

    std::stringstream buffer;
    buffer << t.rdbuf();

    load_text(type, buffer.str());
}

GLuint Shader::value() const {
    return value_;
}

bool Shader::valid() const {
    GLint status;
    glGetShaderiv(value_, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        clog::Log::get()->error("Shader error ", status);
    }

    return status == GL_TRUE;
}

}  // namespace cream
