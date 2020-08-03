#ifndef CREAM_CAMERA_TOP_DOWN_HPP
#define CREAM_CAMERA_TOP_DOWN_HPP

#include <glm/glm.hpp>
#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace cream {

class TopDown : public Camera {
   public:
    TopDown() {
        position_.z = 100.0f;
    }

    [[nodiscard]] glm::mat4 matrix() const override {
        const auto projection =
            glm::ortho(-1.0f * aspect_, 1.0f * aspect_, -1.0f, 1.0f, near_, far_);
        const auto view = glm::lookAt(
            position_, position_ - glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return projection * view;
    }

    [[nodiscard]] auto x() const noexcept {
        return position_.x;
    }

    [[nodiscard]] auto y() const noexcept {
        return position_.y;
    }

    void set_position(const float x, const float y) noexcept {
        position_.x = x;
        position_.y = y;
    }
};

}  // namespace cream

#endif
