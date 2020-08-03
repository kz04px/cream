#ifndef COMPONENT_TRANSFORM_HPP
#define COMPONENT_TRANSFORM_HPP

#include <glm/glm.hpp>

class Transform {
   public:
    constexpr Transform(const float x, const float y) : m_pos({x, y}) {
    }

    constexpr Transform(const glm::vec2 pos) : m_pos(pos) {
    }

    [[nodiscard]] constexpr auto pos() const noexcept {
        return m_pos;
    }

    static const int id;

   private:
    glm::vec2 m_pos;
};

constexpr int Transform::id = 0;

#endif
