#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "assert.hpp"
#include "types.hpp"
#include <queue>

namespace secs {

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
    Entity createEntity() {
        SECS_ASSERT(m_entityCount < MAX_ENTITIES,
                    "Cannot create anymore entities! Max number has already been reached");

        m_entityCount++;
        if (m_unusedIDs.empty())
            return Entity{ m_entityCount };
        const EntityID id = m_unusedIDs.front();
        m_unusedIDs.pop();
        return Entity{ id };
    }
    /// @brief Destroys the given entity and frees up its ID for use.
    void destroyEntity(Entity entity) {
        SECS_ASSERT(entity.id() <= m_entityCount, "Cannot destroy entity with invalid ID!");

        m_unusedIDs.push(entity.id());
        m_entityCount--;
    }
    /**
     * @brief Updates the given entities bitmask to correspond with its new component type.
     * @returns true on success, false otherwise.
     */
    void assignComponent(Entity &entity, ComponentType type) const {
        const auto pos = static_cast<size_t>(type);
        SECS_ASSERT(!entity.test(pos), "This entity already has this component assigned.");
        entity.flip(pos);
    }
    /**
     * @brief Removes the given entities bitmask corresponding with the component type.
     * @returns true on success, false otherwise.
     */
    void removeComponent(Entity &entity, ComponentType type) const {
        const auto pos = static_cast<size_t>(type);
        SECS_ASSERT(entity.test(pos), "This entity already has this component assigned.");
        entity.flip(pos);
    }

private:
    /// @brief The amount of alive entities active.
    uint32_t m_entityCount = 0;
    /// @brief Any unused entity IDs from entities that have been removed.
    std::queue<EntityID> m_unusedIDs{};
};

} // namespace secs
