#pragma once

#include "Scene.hpp"
#include "System.hpp"
#include "components/TextureComponent.hpp"
#include "components/TransformComponent.hpp"

namespace secs {
/**
 * This system handles Rendering all Entities that have the following:
 * - TextureComponent
 * - TransformComponent
 */
class RenderSystem final : public System {
    void update(const float deltaTime, Scene &scene) override {
        for (const auto e : scene.getComponentEntities<TextureComponent, TransformComponent>()) {
            // TODO: Perform Rendering Logic here i guess? Do i even want a renderer like this?
        }
    }
};
} // namespace secs
