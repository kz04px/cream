#ifndef CREAM_LINE_HPP
#define CREAM_LINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "../programs/programs.hpp"

namespace cream {

class Camera;

namespace renderer {

class Line {
   public:
    Line();

    ~Line();

    void buffer() noexcept;

    void render(const Camera &camera) const noexcept;

    void add_line(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &colour) noexcept {
        vertices_.push_back(p1);
        vertices_.push_back(p2);
        colours_.push_back(colour);
        colours_.push_back(colour);
    }

    void clear() noexcept {
        vertices_.clear();
        colours_.clear();
    }

   private:
    GLuint vao_;
    // Mesh
    GLuint vbo_;  // Vertices
    GLuint cbo_;  // Colours
    // Program
    Program program_;
    // Buffers
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> colours_;
};

}  // namespace renderer

}  // namespace cream

#endif
