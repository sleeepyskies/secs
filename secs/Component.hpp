#pragma once

#include "util/secsTypes.hpp"

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

/**
 * @brief Each @ref Component must return their respective enum of this type using type().
 */
enum class ComponentType {
    TEXTURE_COMPONENT  = 0,
    POSITION_COMPONENT = 1,
    CAMERA_COMPONENT = 2,
    // ...
};

/**
 *@brief The base Component class that all other Components must implement.
*/
struct Component {
    ComponentID id                     = ComponentIDGenerator::id();
    virtual ~Component()               = default;
    virtual ComponentType type() const = 0;
};

} // namespace secs
