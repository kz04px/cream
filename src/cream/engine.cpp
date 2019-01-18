#include <iostream>
#include <sstream>
#include <cassert>
#include <ctime>
#include <bits/stdc++.h>
#include "engine.hpp"
#include "window/linux-window.hpp"
#include "events/event.hpp"
#include "events/mouse-event.hpp"
#include "events/window-event.hpp"

namespace cream
{
    Engine::Engine() : log_("log.txt"), window_("3D Game Engine", 480, 480)
    {
        log_.info("Engine loaded");
        start_ = time(0);
        window_.set_callback(std::bind(&Engine::on_event, this, std::placeholders::_1));
    }

    Engine::~Engine()
    {
        log_.info("Engine exited");
    }

    void Engine::on_event(Event &e)
    {
        switch(e.type())
        {
            case EventType::WindowCloseEvent:
                on_window_close(e);
                break;
            default:
                break;
        }
    }

    bool Engine::on_window_close(Event &e)
    {
        stop();
        return true;
    }

    void Engine::load_settings(const std::string path)
    {
        std::ifstream file(path);
        if(!file.is_open())
        {
            log_.warning("Settings file " + path + " not found.");
            return;
        }
        log_.info("Loading settings file " + path);

        std::string line;
        while(getline(file, line))
        {
            if(line.length() <= 1)
            {
                continue;
            }

            if(line[0] == '[' || line[0] == '#' || line[0] == ';')
            {
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

            if(parameter == "debug")
            {
                if(value == "true" || value == "1")
                {
                    debug_ = true;
                }
            }
        }
    }

    bool Engine::run() const
    {
        return run_;
    }

    void Engine::stop()
    {
        run_ = false;
    }

    void Engine::print() const
    {
        std::cout << "debug_ = " << debug_ << std::endl;
        std::cout << "frame_ = " << frame_ << std::endl;
    }

    void Engine::update()
    {
        window_.update();

        frame_++;
    }
}
