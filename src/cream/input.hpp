#ifndef CREAM_INPUT_HPP
#define CREAM_INPUT_HPP

#include <cassert>
#include "keys.hpp"

namespace cream {

namespace inputs {

extern bool key_states[512];

static bool is_key_pressed(const Keys key) {
    assert(0 <= key && key < 512);
    return key_states[key];
}

}  // namespace inputs

}  // namespace cream

#endif
