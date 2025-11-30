#pragma once

#include <bitset>
#include <unordered_map>
#include <vector>

#include "ComponentBitMap.hpp"
#include "ECSProperties.hpp"
#include "EntityHandle.hpp"


namespace secs
{





/**
 * @brief Responsible for the creation, destruction and invalidation of EntityHandle's, as well as
 * managing the ComponentMask of each entity.
 */
class EntityManager
{
public:
    /// @brief A bitmask used to indicate what components an entity has assigned.
    using ComponentMask = std::bitset<MAX_COMPONENTS>;

    /// @brief Creates a new entity.
    EntityHandle create()
    {
        const EntityHandle e = EntityHandle::create();

        SecsAssert(e, "Created invalid entity (idk how).");
        SecsAssert(!m_entityToMask.contains(e), "Created already existing entity");
        SecsAssert(!m_entityToIndex.contains(e), "Created already existing entity");

        m_entityToMask[e] = ComponentMask{ };
        m_alive.push_back(e);
        m_entityToIndex[e] = m_alive.size() - 1;

        return e;
    }

    /// @brief Invalidates the entity and erases its mask.
    void destroy(EntityHandle entity)
    {
        if (!entity) { return; }

        m_alive[m_entityToIndex[entity]]                  = m_alive.back();
        m_entityToIndex[m_alive[m_entityToIndex[entity]]] = m_entityToIndex[entity];

        m_alive.pop_back();

        m_entityToIndex.erase(entity);
        m_entityToMask.erase(entity);
        entity.invalidate();
    }


    /// @brief Returns all entities that have the component bits set in the mask
    std::vector<EntityHandle> getWith(ComponentMask components) const
    {
        // This is probably the best solution with the current setup, but might have to rework whole ecs
        // if things start slowing down
        std::vector<EntityHandle> entities{ };
        for (const auto& [handle, mask] : m_entityToMask) {
            if ((mask & components) == components) { entities.push_back(handle); }
        }
        return entities;
    }

    /// @brief Returns all entities
    std::vector<EntityHandle> getAll() const
    {
        return m_alive;
    }

    /// @brief Updates the given entities bitmask to correspond with its new component type.
    template <typename T>
    void add(const EntityHandle entity)
    {
        if (!entity) { return; }
        if (!m_entityToMask.contains(entity)) { return; }

        m_entityToMask[entity].set(ComponentBitMap::getBitIndex<T>());
    }

    /// @brief Removes the given entities bitmask corresponding with the component type.
    template <typename T>
    void remove(EntityHandle& entity)
    {
        if (!entity) { return; }
        if (!m_entityToMask.contains(entity)) { return; }

        m_entityToMask[entity].reset(ComponentBitMap::getBitIndex<T>());
    }

private:
    std::unordered_map<EntityHandle, ComponentMask> m_entityToMask{ };
    std::unordered_map<EntityHandle, size_t> m_entityToIndex{ };
    std::vector<EntityHandle> m_alive{ };
};

} // namespace siren::ecs
