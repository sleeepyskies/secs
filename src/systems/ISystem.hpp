#pragma once

namespace secs {

class Scene;

/**
 * @brief The interface that all systems must implement. Allows for the data held in Component
 * objects to be changed dynamically during the runtime of the engine.
 */
class ISystem {
public:
    virtual ~ISystem() = default;

    /// @brief Handles updating this systems logic.
    virtual void update(const float deltaTime, const Scene &scene) = 0;
};

} // namespace secs
