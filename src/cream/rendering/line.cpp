#include "line.hpp"
#include <clog/clog.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../camera/camera.hpp"
#include "../shaders/shaders.hpp"

namespace cream {

namespace renderer {

Line::Line() {
    // Program
    auto vs =
        Shader::from_file(ShaderType::VERTEX_SHADER, "./resources/shaders/line/vertex_shader.glsl");
    auto fs = Shader::from_file(ShaderType::FRAGMENT_SHADER,
                                "./resources/shaders/line/fragment_shader.glsl");
    program_.attach(vs);
    program_.attach(fs);
    program_.link();
    program_.detach(vs);
    program_.detach(fs);

    program_.use();

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // Vertices
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));

    // Colours
    glGenBuffers(1, &cbo_);
    glBindBuffer(GL_ARRAY_BUFFER, cbo_);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));
}

Line::~Line() {
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &cbo_);
    glDeleteVertexArrays(1, &vao_);
}

void Line::buffer() noexcept {
    glBindVertexArray(vao_);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), &vertices_[0], GL_STATIC_DRAW);
    // Colours
    glBindBuffer(GL_ARRAY_BUFFER, cbo_);
    glBufferData(
        GL_ARRAY_BUFFER, colours_.size() * sizeof(glm::vec3), &colours_[0], GL_STATIC_DRAW);
}

void Line::render(const Camera &camera) const noexcept {
    if (vertices_.size() == 0) {
        return;
    }

#ifndef NDEBUG
    if (vertices_.size() % 2 == 1) {
        clog::Log::get()->warn("OH NO");
    }
#endif

    program_.use();

    glm::mat4 view = camera.matrix();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));
    glBindVertexArray(vao_);
    glDrawArrays(GL_LINES, 0, vertices_.size());
}

}  // namespace renderer

}  // namespace cream
