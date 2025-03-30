#pragma once

#include "Component.hpp"

namespace secs {


struct TextureComponent : Component {
    size_t textureIndex;

    TextureComponent(const size_t textureIndex) : Component(), textureIndex(textureIndex) {
    }

    ComponentType type() const override { return ComponentType::TEXTURE_COMPONENT; }
};


} // namespace secs
