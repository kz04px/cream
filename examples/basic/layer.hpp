#ifndef LAYER_HPP
#define LAYER_HPP

#include <cassert>
#include <cream/cream.hpp>
#include "components/render.hpp"
#include "components/transform.hpp"
#include "systems/render.hpp"

class GameLayer : public cream::Layer {
   public:
    GameLayer() {
        // Register components
        m_ecs.reg<Transform>();
        m_ecs.reg<Render>();

        assert(m_ecs.registered<Transform>());
        assert(m_ecs.registered<Render>());

        // Create entities
        {
            auto e = m_ecs.create();
            m_ecs.add<Transform>(e, 0.0f, 0.0f);
            m_ecs.add<Render>(e, 0, 255, 0, 0);
        }
        {
            auto e = m_ecs.create();
            m_ecs.add<Transform>(e, 0.5f, 0.5f);
            m_ecs.add<Render>(e, 1, 0, 0, 255);
        }
    }

    void on_update() override {
        const float dt = 1.0 / 60;

        // Run ECS
        systems::render(m_ecs, m_camera);
        m_ecs.update();
    }

    void on_mouse_down(cream::MouseDownEvent &event) {
    }

    void on_mouse_move(cream::MouseMoveEvent &event) {
        static int last_screen_x = event.x();
        static int last_screen_y = event.y();

        const int screen_dx = event.x() - last_screen_x;
        const int screen_dy = event.y() - last_screen_y;

        const float dx = static_cast<float>(screen_dx) / 500.0f;
        const float dy = static_cast<float>(screen_dy) / 500.0f;

        if (cream::inputs::is_mouse_pressed(cream::Mouse::RIGHT)) {
            m_camera.set_position(m_camera.x() - dx, m_camera.y() + dy);
        }

        last_screen_x = event.x();
        last_screen_y = event.y();
    }

    void on_key_press(cream::KeyPressEvent &event) {
        switch (event.key()) {
            case cream::CREAM_KEY_ESCAPE:
                break;
            case cream::CREAM_KEY_SPACE:
                break;
            default:
                std::cout << event.key() << " " << event.scancode() << std::endl;
                break;
        }
    }

    void on_window_resize(cream::WindowResizeEvent &event) {
        if (event.height() == 0) {
            return;
        }
        m_camera.aspect(event.width(), event.height());
    }

    void on_event(cream::Event &event) override {
        switch (event.type()) {
            case cream::EventType::MouseDownEvent:
                on_mouse_down(static_cast<cream::MouseDownEvent &>(event));
                break;
            case cream::EventType::MouseMoveEvent:
                on_mouse_move(static_cast<cream::MouseMoveEvent &>(event));
                break;
            case cream::EventType::KeyPressEvent:
                on_key_press(static_cast<cream::KeyPressEvent &>(event));
                break;
            case cream::EventType::WindowResizeEvent:
                on_window_resize(static_cast<cream::WindowResizeEvent &>(event));
                break;
            default:
                break;
        }
    }

   private:
    cream::ECS m_ecs;
    cream::TopDown m_camera;
};

#endif
