#pragma once

#include <chrono>

namespace secs
{


// todo: we dont actually need a base Component struct, we can use type erasure (which we do
//  anyway using std::type_index), to allow any structs to become Components

/// @brief Unique Handle for components. Is not randomly assigned, but sequentially. 0 is an invalid
/// handle.
using ComponentHandle                       = uint32_t;
constexpr ComponentHandle INVALID_COMPONENT = 0;

// ReSharper disable once CppClassCanBeFinal
/**
 * @brief The base Component abstract class that all other Components must implement.
 */
struct Component
{
    Component() : handle(++currentComponentHandle) { }

    [[nodiscard]] ComponentHandle getComponentHandle() const
    {
        return handle;
    }

    virtual ~Component()                       = default;
    Component(Component&)                      = delete; // no copying please
    Component operator=(const Component&)      = delete;
    Component(Component&&) noexcept            = default;
    Component& operator=(Component&&) noexcept = default;

private:
    ComponentHandle handle;
    static inline uint32_t currentComponentHandle = 0;
};

} // namespace siren::ecs
