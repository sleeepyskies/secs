#pragma once

#include "ISystem.hpp"
#include "assert.hpp"
#include "types.hpp"
#include <typeindex>

namespace sle {

class SystemManager {
public:
    SystemManager()  = default;
    ~SystemManager() = default;

    /// @brief Registers and returns a pointer to the new system. There may only be one system of a
    /// type active at a time, since systems of the same type have the same functionality anyway.
    template <typename T> ref<ISystem> registerSystem() {
        SLE_ASSERT(!m_registeredSystems.contains(index<T>()), "This System is already registered.");

        auto system                     = std::make_shared<T>();
        m_registeredSystems[index<T>()] = system;
        return system;
    }

    /// @brief Registers and returns a pointer to the new system. There may only be one system of a
    /// type active at a time, since systems of the same type have the same functionality anyway.
    template <typename T> void unregisterSystem() {
        SLE_ASSERT(m_registeredSystems.contains(index<T>()), "This System is not yet registered.");

        m_registeredSystems.erase(index<T>());
    }

private:
    template <typename T> [[nodiscard]] std::type_index index() const { return std::type_index(typeid(T)); }

private:
    hashmap<std::type_index, ref<ISystem>> m_registeredSystems{};
};

} // namespace sle
