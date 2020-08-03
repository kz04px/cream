#ifndef CREAM_INPUT_HPP
#define CREAM_INPUT_HPP

#include <array>
#include "keys.hpp"

namespace cream {

namespace inputs {

extern std::array<bool, 512> keyboard_states;
extern std::array<bool, 8> mouse_states;

static bool is_key_pressed(const Keys key) {
    return keyboard_states.at(key);
}

static bool is_mouse_pressed(const Mouse button) {
    return mouse_states.at(button);
}

}  // namespace inputs

}  // namespace cream

#endif
