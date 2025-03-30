#include "EntityManager.hpp"

namespace secs {

Entity EntityManager::createEntity() {
    SECS_ASSERT(m_entityCount < MAX_ENTITIES, "Cannot create anymore entities! Max number has already been reached");

    m_entityCount++;
    if (m_unusedIDs.empty())
        return Entity{ m_entityCount };
    const EntityID id = m_unusedIDs.front();
    m_unusedIDs.pop();
    return Entity{ id };
}

void EntityManager::destroyEntity(const Entity entity) {
    SECS_ASSERT(entity.id() <= m_entityCount, "Cannot destroy entity with invalid ID!");

    m_unusedIDs.push(entity.id());
    m_entityCount--;
}

void EntityManager::assignComponent(Entity &entity, ComponentType type) const {
    const auto pos = static_cast<size_t>(type);
    SECS_ASSERT(!entity.test(pos), "This entity already has this component assigned.");
    entity.flip(pos);
}

void EntityManager::removeComponent(Entity &entity, ComponentType type) const {
    const auto pos = static_cast<size_t>(type);
    SECS_ASSERT(entity.test(pos), "This entity already has this component assigned.");
    entity.flip(pos);
}

} // namespace secs
