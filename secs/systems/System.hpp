#pragma once

#include "util/InputData.hpp"

namespace secs {

class Scene;

/**
 * @brief The interface that all systems must implement. Allows for the data held in Component
 * objects to be changed dynamically during the runtime of the engine.
 */
class System {
public:
    virtual ~System() = default;

    /// @brief Handles updating this systems logic.
    virtual void update(float deltaTime, Scene &scene, InputData &inputData) = 0;
};

} // namespace secs
