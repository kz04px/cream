#include "camera.hpp"

namespace cream
{
    glm::mat4 CameraFPS::matrix() const
    {
        const glm::mat4 projection = glm::perspective(fov_, aspect_, near_, far_);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, zoom_));
        view = glm::rotate(view, -pitch_, glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, -yaw_, glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, -position_);

        return projection * view;
    }

    void CameraFPS::move_up(const float &speed)
    {
        position_ += speed*glm::vec3(0.0f, 1.0f, 0.0f);
    }

    void CameraFPS::move_down(const float &speed)
    {
        position_ += speed*glm::vec3(0.0f, -1.0f, 0.0f);
    }

    void CameraFPS::move_forward(const float &speed)
    {
        position_ += speed*glm::vec3(-sin(yaw_), 0.0f, -cos(yaw_));
    }

    void CameraFPS::move_backward(const float &speed)
    {
        position_ += speed*glm::vec3(sin(yaw_), 0.0f, cos(yaw_));
    }

    void CameraFPS::move_left(const float &speed)
    {
        position_ += speed*glm::vec3(-cos(yaw_), 0.0f, sin(yaw_));
    }

    void CameraFPS::move_right(const float &speed)
    {
        position_ += speed*glm::vec3(cos(yaw_), 0.0f, -sin(yaw_));
    }
}
