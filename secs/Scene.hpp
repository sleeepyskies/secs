#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace secs {
/**
 * @brief The Scene class acts as an API for the Entity-Component-System in sle. It manages the lifetime
 * of all ECS related objects, and allows for creation, deletion and updating of these objects.
 */
class Scene {
public:
    Scene()
        : m_entityManager(EntityManager()), m_componentManager(ComponentManager()),
          m_systemManager(SystemManager()) {
    }

    ~Scene() = default;

    /// @brief Create and return a brand-new @ref Entity.
    Entity createEntity() {
        const Entity e = m_entityManager.createEntity();
        SECS_ASSERT(e, "Created invalid entity.");
        return e;
    }

    /// @brief Destroys the given entity.
    void destroyEntity(Entity &entity) {
        SECS_ASSERT(entity, "Cannot destroy an entity that is not alive.");
        m_entityManager.destroyEntity(entity);
        m_componentManager.entityDestroyed(entity);
        entity.kill();
    }

    /// @brief Creates an internal relation between the Entity and the Component in the system.
    /// Note that secs will create a copy of the component passed to store internally, such that
    /// the caller cannot make manual changes to the components passed tos secs.
    template<typename T>
    void registerComponent(Entity &entity, const T &component) {
        SECS_ASSERT(entity, "Cannot register component for entity that is not alive.");
        m_entityManager.assignComponent(entity, component.type());
        m_componentManager.registerComponent<T>(entity, component);
    }

    /// @brief Deletes the relation between the entity and the component of type T.
    template<typename T>
    void unregisterComponent(Entity &entity, const ComponentType type) {
        SECS_ASSERT(entity, "Cannot unregister component for entity that is not alive.");
        m_entityManager.removeComponent(entity, type);
        m_componentManager.unregisterComponent<T>(entity);
    }

    /// @brief Gets the component of type T associated with this entity.
    template<typename T>
    T &getComponent(const Entity entity) {
        SECS_ASSERT(entity, "Cannot get component for entity that is not alive.");
        return m_componentManager.getComponent<T>(entity);
    }

    /// @brief Returns all active components of this type.
    template<typename T>
    ComponentList<T> &getList() { return m_componentManager.getList<T>(); }

    /// @brief Returns all entities that have the given components.
    template<typename... Args>
    std::vector<EntityID> getComponentEntities() {
        std::vector<EntityID> entities{};
        for (const EntityID &e: m_entityManager.entities()) {
            if ((m_componentManager.hasComponent<Args>(e) && ...)) {
                entities.push_back(e);
            }
        }
        return entities;
    }

    /// @brief Registers a system to be active.
    template<typename T>
    ref<System> registerSystem() { return m_systemManager.registerSystem<T>(); }

    /// @brief Unregisters a system.
    template<typename T>
    void unregisterSystem() { m_systemManager.unregisterSystem<T>(); }

private:
    EntityManager m_entityManager;
    ComponentManager m_componentManager;
    SystemManager m_systemManager;
};
} // namespace secs
