#include "model.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../camera/camera.hpp"
#include "../models/mesh.hpp"
#include "../shaders/shaders.hpp"
#include "clog/clog.hpp"

namespace cream {

namespace renderer {

Model::Model() {
    // Program
    auto vs = Shader::from_file(ShaderType::VERTEX_SHADER,
                                "./resources/shaders/model/vertex_shader.glsl");
    auto fs = Shader::from_file(ShaderType::FRAGMENT_SHADER,
                                "./resources/shaders/model/fragment_shader.glsl");
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

    // Normals
    glGenBuffers(1, &nbo_);
    glBindBuffer(GL_ARRAY_BUFFER, nbo_);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));

    // Rotations
    glGenBuffers(1, &rbo_);
    glBindBuffer(GL_ARRAY_BUFFER, rbo_);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));

    // Translations
    glGenBuffers(1, &tbo_);
    glBindBuffer(GL_ARRAY_BUFFER, tbo_);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));
}

Model::~Model() {
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &cbo_);
    glDeleteBuffers(1, &nbo_);
    glDeleteBuffers(1, &rbo_);
    glDeleteBuffers(1, &tbo_);
    glDeleteVertexArrays(1, &vao_);
}

void Model::buffer() noexcept {
    glBindVertexArray(vao_);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), &vertices_[0], GL_STATIC_DRAW);
    // Colours
    glBindBuffer(GL_ARRAY_BUFFER, cbo_);
    glBufferData(
        GL_ARRAY_BUFFER, colours_.size() * sizeof(glm::vec3), &colours_[0], GL_STATIC_DRAW);
    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, nbo_);
    glBufferData(
        GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), &normals_[0], GL_STATIC_DRAW);
    // Rotations
    glBindBuffer(GL_ARRAY_BUFFER, rbo_);
    glBufferData(
        GL_ARRAY_BUFFER, rotations_.size() * sizeof(glm::vec3), &rotations_[0], GL_STATIC_DRAW);
    // Translations
    glBindBuffer(GL_ARRAY_BUFFER, tbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 translations_.size() * sizeof(glm::vec3),
                 &translations_[0],
                 GL_STATIC_DRAW);
}

void Model::add_model(const Mesh &mesh, const glm::vec3 &pos, const glm::vec3 &rot) noexcept {
    // Model
    vertices_.insert(std::end(vertices_), std::begin(mesh.vertices()), std::end(mesh.vertices()));
    colours_.insert(std::end(colours_), std::begin(mesh.colours()), std::end(mesh.colours()));
    normals_.insert(std::end(normals_), std::begin(mesh.normals()), std::end(mesh.normals()));

    for (std::size_t i = 0; i < mesh.vertices().size(); ++i) {
        rotations_.push_back(rot);
        translations_.push_back(pos);
    }
}

void Model::render(const Camera &camera) const noexcept {
    if (vertices_.size() == 0) {
        return;
    }

    program_.use();

    glm::mat4 view = camera.matrix();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
}

}  // namespace renderer

}  // namespace cream
