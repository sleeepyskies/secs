#pragma once

#include "types.hpp"

namespace secs {

/**
 * @brief This class is used by components to make sure they receive a unique ID without much overhead. Note that an id
 * of 0 is considered invalid.
 */
class ComponentIDGenerator {
public:
    static ComponentID id() { return s_currentId++; }
private:
    static inline ComponentID s_currentId = 1;
};

enum class ComponentType {
    TEXTURE_COMPONENT = 0,
    POSITION_COMPONENT = 1
    // ...
};

/// @brief The base Component class that all other Components must implement.
struct IComponent {
    ComponentID id                     = ComponentIDGenerator::id();
    virtual ~IComponent()              = default;
    virtual ComponentType type() const = 0;
};
} // namespace secs
