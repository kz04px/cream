#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace cream {

class Mesh {
   public:
    Mesh();
    ~Mesh();
    void load_obj(const std::string path);
    void print();
    void clear();
    int num_vertices() const {
        return num_vertices_;
    }
    const std::vector<glm::vec3> &vertices() const {
        return vertices_;
    }
    const std::vector<glm::vec3> &colours() const {
        return colours_;
    }
    const std::vector<glm::vec3> &normals() const {
        return normals_;
    }

   private:
    int num_vertices_ = 0;
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> colours_;
    std::vector<glm::vec3> normals_;
};

}  // namespace cream

#endif
