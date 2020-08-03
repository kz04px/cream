#ifndef SYSTEM_RENDER_HPP
#define SYSTEM_RENDER_HPP

#include <cream/ecs.hpp>
#include "../components/render.hpp"
#include "../components/transform.hpp"

namespace systems {

void render(cream::ECS &ecs, cream::Camera &camera) {
    cream::Renderer2D::begin(camera);
    auto entities = ecs.entities<Render, Transform>();
    for (const auto &e : entities) {
        auto &r = ecs.get<Render>(e);
        auto &t = ecs.get<Transform>(e);
        cream::Renderer2D::draw_quad(t.pos(), glm::vec2{1.0f, 1.0f}, r.colour(), r.layer());
    }
    cream::Renderer2D::end();
}

}  // namespace systems

#endif
