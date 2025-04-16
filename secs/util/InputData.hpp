#pragma once

#include <SDL_keycode.h>
#include <glm/vec2.hpp>
#include "secsTypes.hpp"

namespace secs {
/**
 * @brief This struct is used to pass around any input data to the current state.
 */
struct InputData {
    hashmap<SDL_Keycode, bool> keys;
    glm::ivec2 mousePos{ 0, 0 };
    std::array<bool, 5> mouseClicks{};
};
} // namespace secs
