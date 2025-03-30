#pragma once
#include "ISystem.hpp"

namespace secs {
/**
 * This system handles Rendering all Entities that have the following:
 * - TextureComponent
 * - TransformComponent
 */
class RenderSystem final : public ISystem {
    void update(const float deltaTime, const Scene &scene) override {

    }
};
} // namespace secs
