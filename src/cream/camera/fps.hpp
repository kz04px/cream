#ifndef CAMERA_FPS_HPP
#define CAMERA_FPS_HPP

#include <glm/glm.hpp>
#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace cream {

class FPSCamera : public Camera {
   public:
    FPSCamera() : speed_{1.0} {
    }
    glm::mat4 matrix() const override {
        const glm::mat4 projection = glm::perspective(fov_, aspect_, near_, far_);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, zoom_));
        view = glm::rotate(view, -pitch_, glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, -yaw_, glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, -position_);
        return projection * view;
    }
    // Movement
    void move_up(const float dt) {
        position_ += dt * speed_ * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    void move_down(const float dt) {
        position_ += dt * speed_ * glm::vec3(0.0f, -1.0f, 0.0f);
    }
    void move_forward(const float dt) {
        position_ += dt * speed_ * glm::vec3(-sin(yaw_), 0.0f, -cos(yaw_));
    }
    void move_backward(const float dt) {
        position_ += dt * speed_ * glm::vec3(sin(yaw_), 0.0f, cos(yaw_));
    }
    void move_left(const float dt) {
        position_ += dt * speed_ * glm::vec3(-cos(yaw_), 0.0f, sin(yaw_));
    }
    void move_right(const float dt) {
        position_ += dt * speed_ * glm::vec3(cos(yaw_), 0.0f, -sin(yaw_));
    }
    void yaw_add(const float f) {
        yaw_ += f;
    }
    void pitch_add(const float f) {
        pitch_ += f;
    }

   public:
    float speed_;
    // View
    float pitch_ = 0.0;
    float yaw_ = 0.0;
    float roll_ = 0.0;
    // Projection
    float fov_ = 0.45;
    float zoom_ = 1.0;
};

}  // namespace cream

#endif
