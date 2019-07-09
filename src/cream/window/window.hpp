#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <functional>
#include <memory>
#include "../events/event.hpp"

namespace cream {

struct WindowData {
    std::string title_ = "untitled";
    int width_ = 480;
    int height_ = 480;
    bool fullscreen_ = false;
    bool vsync_ = false;
    double mouse_x_ = 0.0;
    double mouse_y_ = 0.0;
    std::function<void(Event &)> callback_;
};

class Window {
   public:
    Window(){};
    virtual void update() = 0;
    void set_callback(const std::function<void(Event &)> &func) {
        data_.callback_ = func;
    }
    // vsync
    bool vsync() {
        return data_.vsync_;
    }
    virtual void vsync(const bool n) = 0;
    // title
    std::string title() {
        return data_.title_;
    }
    virtual void title(const std::string title) = 0;
    // Others
    int width() {
        return data_.width_;
    }
    int height() {
        return data_.height_;
    }
    bool fullscreen() {
        return data_.fullscreen_;
    }
    virtual void resize(const int w, const int h) = 0;

   protected:
    WindowData data_;
};

}  // namespace cream

#endif
