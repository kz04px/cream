#ifndef COMPONENT_RENDER_HPP
#define COMPONENT_RENDER_HPP

#include <cream/colour.hpp>

struct Render {
    constexpr Render(const int layer, const int r, const int g, const int b)
        : m_layer{layer}, m_colour(r, g, b) {
    }

    [[nodiscard]] constexpr auto layer() const noexcept {
        return m_layer;
    }

    [[nodiscard]] constexpr auto colour() const noexcept {
        return m_colour;
    }

    int m_layer;
    cream::Colour m_colour;
    static const int id;
};

const int Render::id = 1;

#endif
