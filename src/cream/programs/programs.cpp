#include "programs.hpp"
#include <algorithm>
#include "../shaders/shaders.hpp"
#include "clog/clog.hpp"

namespace cream {

Program::Program() {
    program_ = glCreateProgram();
    clog::Log::get()->info("Program created (", value(), ")");
}

Program::~Program() {
    clog::Log::get()->info("Program destroyed (", value(), ")");
    glDeleteProgram(program_);
}

void Program::link() {
    glLinkProgram(program_);

    linked_ = true;
}

bool Program::valid() const {
    GLint status;
    glGetProgramiv(program_, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        clog::Log::get()->error("ERROR Program ", program_, " code ", status);
    }

    return status == GL_TRUE;
}

void Program::attach(const Shader &shader) {
    auto it = find(shaders_.begin(), shaders_.end(), shader.value());
    if (it == shaders_.end()) {
        clog::Log::get()->info("Program ", value(), " attach shader ", shader.value());
        shaders_.push_back(shader.value());
        glAttachShader(program_, shader.value());
    }
}

void Program::detach(const Shader &shader) {
    auto it = find(shaders_.begin(), shaders_.end(), shader.value());
    if (it != shaders_.end()) {
        clog::Log::get()->info("Program ", value(), " detach shader ", shader.value());
        shaders_.erase(it);
        glDetachShader(program_, shader.value());
    }
}

void Program::use() const {
    if (linked_) {
        glUseProgram(program_);
    }
}

GLuint Program::value() const {
    return program_;
}

}  // namespace cream
