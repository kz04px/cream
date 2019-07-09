#ifndef INSTANCE_HPP_INCLUDED
#define INSTANCE_HPP_INCLUDED

#include "../models/mesh.hpp"

namespace cream {

class Instance {
   public:
    Instance();
    ~Instance();
    void buffer_mesh(const Mesh &mesh);
    void buffer_instances(const std::vector<glm::vec3> &rotations,
                          const std::vector<glm::vec3> &translations,
                          const std::vector<glm::vec3> &scales);
    void render() const;

   private:
    int num_vertices_ = 0;
    int num_instances_ = 0;
    unsigned int vao_;
    // Mesh
    unsigned int vbo_;  // Vertices
    unsigned int cbo_;  // Colours
    unsigned int nbo_;  // Normals
    // Instances
    unsigned int rbo_;  // Rotations
    unsigned int tbo_;  // Translations
    unsigned int sbo_;  // Scales
};

}  // namespace cream

#endif
