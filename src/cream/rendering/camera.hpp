#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cream {

class Camera {
   public:
    glm::mat4 matrix() const;
    void eye(const glm::vec3 &v) {
        eye_ = v;
    }
    void center(const glm::vec3 &v) {
        center_ = v;
    }
    void up(const glm::vec3 &v) {
        up_ = v;
    }
    void fov(const float &f) {
        fov_ = f;
    }
    void aspect(const float &f) {
        aspect_ = f;
    }
    void aspect(const int &w, const int &h) {
        aspect_ = (float)w / h;
    }

   private:
    glm::vec3 eye_{5.0, 5.0, 5.0};
    glm::vec3 center_{0.0, 0.0, 0.0};
    glm::vec3 up_{0.0, 1.0, 0.0};
    float fov_ = 0.45;
    float aspect_ = 1.0;
    float near_ = 0.1;
    float far_ = 1000.0;
};

class CameraFPS {
   public:
    glm::mat4 matrix() const;
    void position(const glm::vec3 &v) {
        position_ = v;
    }
    // View
    void pitch(const float &f) {
        pitch_ = f;
    }
    void yaw(const float &f) {
        yaw_ = f;
    }
    void roll(const float &f) {
        roll_ = f;
    }
    // Projection
    void fov(const float &f) {
        fov_ = f;
    }
    void aspect(const float &f) {
        aspect_ = f;
    }
    void aspect(const int &w, const int &h) {
        aspect_ = (float)w / h;
    }
    // Movement
    void move_up(const float &speed);
    void move_down(const float &speed);
    void move_forward(const float &speed);
    void move_backward(const float &speed);
    void move_left(const float &speed);
    void move_right(const float &speed);
    // View changes
    void pitch_add(const float &f) {
        pitch_ += f;
    }
    void yaw_add(const float &f) {
        yaw_ += f;
    }
    void roll_add(const float &f) {
        roll_ += f;
    }

   private:
    glm::vec3 position_{0.0, 0.0, 15.0};
    // View
    float pitch_ = 0.0;
    float yaw_ = 0.0;
    float roll_ = 0.0;
    // Projection
    float fov_ = 0.45;
    float aspect_ = 1.0;
    float near_ = 0.1;
    float far_ = 1000.0;
    float zoom_ = 1.0;
};

}  // namespace cream

#endif
