#pragma once

#include "Component.hpp"
#include <glm/vec2.hpp>

namespace secs {
    /// @brief This holds information on camera specific parameters.
    struct CameraComponent : public Component {
        explicit CameraComponent(const float speed = 5.f)
            : speed(speed) {}

        float speed = 0.f;
    };
} //  namespace secs
