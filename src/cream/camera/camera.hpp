#ifndef CREAM_CAMERA_HPP
#define CREAM_CAMERA_HPP

#include <glm/glm.hpp>

namespace cream {

class Camera {
   public:
    Camera() : position_{0.0, 0.0, 0.0}, aspect_{0.1}, near_{0.1}, far_{1000.0} {
    }

    virtual glm::mat4 matrix() const = 0;

    void aspect(const float w, const float h) {
        if (h == 0.0) {
            return;
        }
        aspect_ = w / h;
    }

   public:
    glm::vec3 position_;
    float aspect_;
    float near_;
    float far_;
};

}  // namespace cream

#endif
