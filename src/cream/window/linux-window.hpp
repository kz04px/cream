#ifndef CREAM_LINUX_WINDOW_HPP
#define CREAM_LINUX_WINDOW_HPP

#include <string>
#include "window.hpp"

struct GLFWwindow;

// TODO:
// -- Use std::unique_ptr

namespace cream {

class LinuxWindow : public Window {
   public:
    LinuxWindow(const std::string &title, const int width, const int height);
    ~LinuxWindow();
    void title(const std::string &title) override;
    void vsync(const bool n) override;
    void update() override;
    void clear();
    void swap_buffer();
    void poll_events();
    void resize(const int w, const int h) override;
    void hide_mouse() override;
    void show_mouse() override;

   private:
    GLFWwindow *window_ = nullptr;
    // std::unique_ptr<GLFWwindow> window_;
};

}  // namespace cream

#endif
