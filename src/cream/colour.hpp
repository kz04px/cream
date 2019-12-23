#ifndef CREAM_COLOUR_HPP
#define CREAM_COLOUR_HPP

namespace cream {

struct Colour {
    constexpr Colour() : r{0.0}, g{0.0}, b{0.0}, a{1.0} {
    }

    constexpr Colour(const float r_, const float g_, const float b_, const float a_ = 1.0)
        : r{r_}, g{g_}, b{b_}, a{a_} {
    }

    [[nodiscard]] static constexpr Colour black() noexcept {
        return Colour(0.0, 0.0, 0.0);
    }

    [[nodiscard]] static constexpr Colour white() noexcept {
        return Colour(1.0, 1.0, 1.0);
    }

    [[nodiscard]] static constexpr Colour red() noexcept {
        return Colour(1.0, 0.0, 0.0);
    }

    [[nodiscard]] static constexpr Colour green() noexcept {
        return Colour(0.0, 1.0, 0.0);
    }

    [[nodiscard]] static constexpr Colour blue() noexcept {
        return Colour(0.0, 0.0, 1.0);
    }

    [[nodiscard]] static constexpr Colour sky_blue() noexcept {
        return Colour(0.529, 0.808, 0.922);
    }

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    float a = 0.0;
};

}  // namespace cream

#endif
