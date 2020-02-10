#include "instance.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../camera/camera.hpp"
#include "../models/mesh.hpp"
#include "../shaders/shaders.hpp"

namespace cream {

Instance::Instance() {
    // Program
    auto vs = Shader::from_file(ShaderType::VERTEX_SHADER,
                                "./resources/shaders/instance/vertex_shader.glsl");
    auto fs = Shader::from_file(ShaderType::FRAGMENT_SHADER,
                                "./resources/shaders/instance/fragment_shader.glsl");
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
    glVertexAttribDivisor(3, 1);

    // Translations
    glGenBuffers(1, &tbo_);
    glBindBuffer(GL_ARRAY_BUFFER, tbo_);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));
    glVertexAttribDivisor(4, 1);

    // Scales
    glGenBuffers(1, &sbo_);
    glBindBuffer(GL_ARRAY_BUFFER, sbo_);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, (char *)0 + 0 * sizeof(GLfloat));
    glVertexAttribDivisor(5, 1);
}

Instance::~Instance() {
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &cbo_);
    glDeleteBuffers(1, &nbo_);
    glDeleteBuffers(1, &rbo_);
    glDeleteBuffers(1, &tbo_);
    glDeleteBuffers(1, &sbo_);
    glDeleteVertexArrays(1, &vao_);
}

void Instance::buffer_mesh(const Mesh &mesh) {
    assert(mesh.vertices().size() == mesh.colours().size());
    assert(mesh.vertices().size() == mesh.normals().size());

    num_vertices_ = mesh.num_vertices();

    glBindVertexArray(vao_);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh.vertices().size() * sizeof(glm::vec3),
                 &mesh.vertices()[0],
                 GL_STATIC_DRAW);
    // Colours
    glBindBuffer(GL_ARRAY_BUFFER, cbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh.colours().size() * sizeof(glm::vec3),
                 &mesh.colours()[0],
                 GL_STATIC_DRAW);
    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, nbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh.normals().size() * sizeof(glm::vec3),
                 &mesh.normals()[0],
                 GL_STATIC_DRAW);
}

void Instance::buffer_instances(const std::vector<glm::vec3> &rotations,
                                const std::vector<glm::vec3> &translations,
                                const std::vector<float> &scales) {
    assert(rotations.size() == translations.size());
    assert(rotations.size() == scales.size());

    num_instances_ = rotations.size();

    glBindVertexArray(vao_);

    // Rotations
    glBindBuffer(GL_ARRAY_BUFFER, rbo_);
    glBufferData(
        GL_ARRAY_BUFFER, rotations.size() * sizeof(glm::vec3), &rotations[0], GL_STATIC_DRAW);
    // Translations
    glBindBuffer(GL_ARRAY_BUFFER, tbo_);
    glBufferData(
        GL_ARRAY_BUFFER, translations.size() * sizeof(glm::vec3), &translations[0], GL_STATIC_DRAW);
    // Scales
    glBindBuffer(GL_ARRAY_BUFFER, sbo_);
    glBufferData(GL_ARRAY_BUFFER, scales.size() * sizeof(float), &scales[0], GL_STATIC_DRAW);
}

void Instance::render(const Camera &camera) const {
    assert(num_vertices_ >= 0);
    assert(num_instances_ >= 0);

    if (num_vertices_ == 0 || num_instances_ == 0) {
        return;
    }

    program_.use();

    glm::mat4 view = camera.matrix();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));
    glBindVertexArray(vao_);
    glDrawArraysInstanced(GL_TRIANGLES, 0, num_vertices_, num_instances_);
}

}  // namespace cream
