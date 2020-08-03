#ifndef CREAM_MATERIALS_HPP
#define CREAM_MATERIALS_HPP

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace cream {

struct Material {
    std::string name_ = "";
    float ns_ = 1.0;
    glm::vec3 ka_ = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 kd_ = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 ks_ = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 ke_ = glm::vec3(1.0, 1.0, 1.0);
    float ni_ = 1.0;
    float d_ = 1.0;
    int illum_ = 1;
};

class Materials {
   public:
    void load(const std::string &path);
    void add(Material &material);
    bool has(const std::string &name) const;
    Material &find(const std::string &name);
    void erase(const std::string &name);
    void print() const;

   private:
    Material basic_;
    std::unordered_map<std::string, Material> materials_;
};

}  // namespace cream

#endif
