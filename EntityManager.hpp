#pragma once

#include "IComponent.hpp"
#include "assert.hpp"
#include "types.hpp"
#include "Entity.hpp"
#include <queue>

namespace sle {

/**
 * @brief The EntityManager is responsible for managing Entities. This means creating and destroying
 * entities, as well as managing the IDs of destroyed entities to reuse them. Furthermore, when
 *  registering components, the EntityManager will update the entities @ref ComponentMask.
 */
class EntityManager {
public:
    EntityManager()  = default;
    ~EntityManager() = default;

    /// @brief Creates a new Entity with the first available ID, if there are any available.
    Entity createEntity();
    /// @brief Destroys the given entity and frees up its ID for use.
    void destroyEntity(Entity entity);
    /**
     * @brief Updates the given entities bitmask to correspond with its new component type.
     * @returns true on success, false otherwise.
     */
    void assignComponent(Entity &entity, ComponentType type) const;
    /**
     * @brief Removes the given entities bitmask corresponding with the component type.
     * @returns true on success, false otherwise.
     */
    void removeComponent(Entity &entity, ComponentType type) const;

private:
    /// @brief The amount of alive entities active.
    uint32_t m_entityCount = 0;
    /// @brief Any unused entity IDs from entities that have been removed.
    std::queue<EntityID> m_unusedIDs{};
};

} // namespace sle
