#ifndef INSTANCE_HPP_INCLUDED
#define INSTANCE_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "../programs/programs.hpp"

namespace cream {

class Mesh;
class Camera;

class Instance {
   public:
    Instance();
    ~Instance();
    void buffer_mesh(const Mesh &mesh);
    void buffer_instances(const std::vector<glm::vec3> &rotations,
                          const std::vector<glm::vec3> &translations,
                          const std::vector<float> &scales);
    void render(const Camera &camera) const;

   private:
    int num_vertices_ = 0;
    int num_instances_ = 0;
    GLuint vao_;
    // Mesh
    GLuint vbo_;  // Vertices
    GLuint cbo_;  // Colours
    GLuint nbo_;  // Normals
    // Instances
    GLuint rbo_;  // Rotations
    GLuint tbo_;  // Translations
    GLuint sbo_;  // Scales
    // Program
    Program program_;
};

}  // namespace cream

#endif
