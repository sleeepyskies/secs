#pragma once

#include "Component.hpp"
#include <SDL.h>

namespace secs {

struct TransformComponent : Component {
    SDL_Rect position;

    explicit TransformComponent(const SDL_Rect rect) : Component(), position(rect) {}
    ComponentType type() const override { return ComponentType::POSITION_COMPONENT; }
};

} // namespace secs
