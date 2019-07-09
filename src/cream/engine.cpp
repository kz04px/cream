#include "engine.hpp"
#include <bits/stdc++.h>
#include <cassert>
#include <ctime>
#include <iostream>
#include <sstream>
#include "events/event.hpp"
#include "events/mouse-event.hpp"
#include "events/window-event.hpp"
#include "window/linux-window.hpp"

namespace cream {

Engine::Engine() : window_("3D Game Engine", 480, 480) {
    clog::Log::get()->info("Engine loaded");
    start_ = time(0);
    window_.set_callback(std::bind(&Engine::on_event, this, std::placeholders::_1));
}

Engine::~Engine() {
    clog::Log::get()->info("Engine exited");
}

void Engine::on_event(Event &e) {
    switch (e.type()) {
        case EventType::WindowCloseEvent:
            on_window_close(e);
            return;
            break;
        default:
            break;
    }

    layer_manager_.pass_event(e);
}

bool Engine::on_window_close(Event &e) {
    stop();
    return true;
}

void Engine::load_settings(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        clog::Log::get()->warn("Settings file ", path, " not found.");
        return;
    }
    clog::Log::get()->info("Loading settings file ", path);

    std::string line;
    while (getline(file, line)) {
        if (line.length() <= 1) {
            continue;
        }

        if (line[0] == '[' || line[0] == '#' || line[0] == ';') {
            continue;
        }

        std::stringstream iss(line);

        std::string parameter;
        std::string value;

        getline(iss, parameter, '=');
        getline(iss, value, '=');

        // Case insensitive
        transform(parameter.begin(), parameter.end(), parameter.begin(), ::tolower);
        transform(value.begin(), value.end(), value.begin(), ::tolower);

        if (parameter == "debug") {
            if (value == "true" || value == "1") {
                debug_ = true;
            }
        }
    }
}

bool Engine::run() const {
    return run_;
}

void Engine::stop() {
    run_ = false;
}

void Engine::print() const {
    std::cout << "debug_ = " << debug_ << std::endl;
    std::cout << "frame_ = " << frame_ << std::endl;
}

void Engine::push_layer(Layer *layer) {
    layer_manager_.push_layer(layer);
}

void Engine::update() {
    window_.clear();

    layer_manager_.update();

    window_.swap_buffer();
    window_.poll_events();

    frame_++;
}

}  // namespace cream
