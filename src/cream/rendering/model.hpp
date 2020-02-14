#ifndef RENDERER_MODEL_HPP
#define RENDERER_MODEL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "../programs/programs.hpp"

namespace cream {

class Mesh;
class Camera;

namespace renderer {

class Model {
   public:
    Model();

    ~Model();

    void buffer() noexcept;

    void render(const Camera &camera) const noexcept;

    void add_model(const Mesh &mesh, const glm::vec3 &pos, const glm::vec3 &rot) noexcept;

    void clear() noexcept {
        vertices_.clear();
        colours_.clear();
        normals_.clear();
        rotations_.clear();
        translations_.clear();
    }

   private:
    GLuint vao_;
    // Mesh
    GLuint vbo_;  // Vertices
    GLuint cbo_;  // Colours
    GLuint nbo_;  // Normals
    GLuint rbo_;  // Rotations
    GLuint tbo_;  // Translations
    // Program
    Program program_;
    // Buffers
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> colours_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec3> rotations_;
    std::vector<glm::vec3> translations_;
};

}  // namespace renderer

}  // namespace cream

#endif
