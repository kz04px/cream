#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <string>
#include "logging/logging.hpp"
#include "window/linux-window.hpp"
#include "events/event.hpp"
#include "layers/layer-manager.hpp"

namespace cream
{
    const std::string version_major = "0";
    const std::string version_minor = "1";
    const std::string version       = version_major + "." + version_minor;
    const std::string build         = std::string(__TIME__) + " " + std::string(__DATE__);
    const std::string author        = "kz04px";
    const std::string url           = "https://github.com/kz04px/cream";
    const std::string about         = "Cream is a small 3D game engine written in C++";

    class Engine
    {
        public:
            Engine();
            ~Engine();
            void load_settings(const std::string path);
            bool run() const;
            void stop();
            void update();
            void print() const;
            // Events
            void on_event(Event &e);
            bool on_window_close(Event &e);
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
}

#endif
