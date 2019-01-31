#include "camera.hpp"

namespace cream
{
    glm::mat4 Camera::matrix() const
    {
        const glm::mat4 projection = glm::ortho(-20.0f*aspect_, 20.0f*aspect_, -20.0f, 20.0f, near_, far_);
        const glm::mat4 view = glm::lookAt(eye_, center_, up_);
        return projection * view;
    }
}
