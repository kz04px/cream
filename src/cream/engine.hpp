#ifndef CREAM_ENGINE_HPP
#define CREAM_ENGINE_HPP

#include <string>
#include "colour.hpp"
#include "layers/layer-manager.hpp"
#include "window/linux-window.hpp"

namespace cream {

class Event;
class Layer;
class MouseDownEvent;
class MouseUpEvent;
class KeyPressEvent;
class KeyReleaseEvent;
class WindowCloseEvent;
class WindowResizeEvent;

const std::string version_major = "0";
const std::string version_minor = "1";
const std::string version = version_major + "." + version_minor;
const std::string build = std::string(__TIME__) + " " + std::string(__DATE__);
const std::string author = "kz04px";
const std::string url = "https://github.com/kz04px/cream";
const std::string about = "Cream is a small 3D game engine written in C++";

class Engine {
   public:
    Engine();
    ~Engine();
    void load_settings(const std::string &path);
    bool run() const;
    void stop();
    void update();
    void print() const;
    void set_clear_colour(const Colour &colour) noexcept {
        window_.set_clear_colour(colour);
    }
    // Events
    void on_event(Event &e);
    bool on_mouse_down(MouseDownEvent &e);
    bool on_mouse_up(MouseUpEvent &e);
    bool on_key_press(KeyPressEvent &e);
    bool on_key_release(KeyReleaseEvent &e);
    bool on_window_close(WindowCloseEvent &e);
    bool on_window_resize(WindowResizeEvent &e);
    // Layers
    void push_layer(Layer *layer);

   private:
    // Engine statistics
    clock_t start_;
    std::uint64_t frame_ = 0;
    // State
    bool run_ = true;
    bool debug_ = false;
    // Other
    LinuxWindow window_;
    LayerManager layer_manager_;
};

}  // namespace cream

#endif
