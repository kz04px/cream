#ifndef LINUX_WINDOW_HPP_INCLUDED
#define LINUX_WINDOW_HPP_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

// TODO:
// -- Use std::unique_ptr

namespace cream {

class LinuxWindow : public Window {
   public:
    LinuxWindow(const std::string title, const int width, const int height);
    ~LinuxWindow();
    void title(const std::string title) override;
    void vsync(const bool n) override;
    void update() override;
    void clear();
    void swap_buffer();
    void poll_events();
    void resize(const int w, const int h) override;

   private:
    GLFWwindow *window_ = nullptr;
    // std::unique_ptr<GLFWwindow> window_;
};

}  // namespace cream

#endif
