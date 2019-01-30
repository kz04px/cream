#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cream
{
    class Camera
    {
    	public:
    		glm::mat4 matrix() const;
    		void eye(const glm::vec3 &v) {eye_ = v;}
    		void center(const glm::vec3 &v) {center_ = v;}
    		void up(const glm::vec3 &v) {up_ = v;}
    		void fov(const float &f) {fov_ = f;}
    		void aspect(const float &f) {aspect_ = f;}
    		void aspect(const int &w, const int &h) {aspect_ = (float)w/h;}
    	private:
    		glm::vec3 eye_{5.0, 5.0, 5.0};
    		glm::vec3 center_{0.0, 0.0, 0.0};
    		glm::vec3 up_{0.0, 1.0, 0.0};
    		float fov_ = 0.45;
    		float aspect_ = 1.0;
    		float near_ = 0.1;
    		float far_ = 1000.0;
    };

    glm::mat4 Camera::matrix() const
    {
    	const glm::mat4 projection = glm::ortho(-20.0f*aspect_, 20.0f*aspect_, -20.0f, 20.0f, near_, far_);
    	const glm::mat4 view = glm::lookAt(eye_, center_, up_);
    	return projection * view;
    }
}

#endif
