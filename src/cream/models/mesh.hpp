#ifndef CREAM_MESH_HPP
#define CREAM_MESH_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace cream {

class Mesh {
   public:
    Mesh();
    ~Mesh();
    void load_obj(const std::string &directory, const std::string &filename);
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
    const std::vector<glm::vec2> &uvs() const {
        return uvs_;
    }

   private:
    int num_vertices_ = 0;
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> colours_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec2> uvs_;
};

}  // namespace cream

#endif
