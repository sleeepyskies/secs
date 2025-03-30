#pragma once

#include "IComponent.hpp"
#include <SDL.h>

namespace sle {

struct TransformComponent : IComponent {
    SDL_Rect position;

    explicit TransformComponent(const SDL_Rect rect) : IComponent(), position(rect) {}
    ComponentType type() const override { return ComponentType::POSITION_COMPONENT; }
};

} // namespace sle
