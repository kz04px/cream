#ifndef LINUX_WINDOW_HPP_INCLUDED
#define LINUX_WINDOW_HPP_INCLUDED

#include <GLFW/glfw3.h>
#include "window.hpp"

// TODO:
// -- Use std::unique_ptr

namespace cream
{
    class LinuxWindow : public Window
    {
        public:
            LinuxWindow(const std::string title, const int width, const int height);
            ~LinuxWindow();
            void title(const std::string title) override;
            void vsync(const bool n) override;
            void update() override;
        private:
            GLFWwindow *window_ = nullptr;
            //std::unique_ptr<GLFWwindow> window_;
    };
}

#endif
