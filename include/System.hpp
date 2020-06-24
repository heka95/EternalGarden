#pragma once
#include <set>
#include "core/ECSTypes.hpp"

namespace Garden
{
    class Manager;

    class System
    {
    public:
        System(int priority, std::set<ComponentType> needed, Manager *manager) : m_priority(priority), m_needed(needed), m_manager(manager) {}
        virtual ~System() = default;
        int getpriority() const { return m_priority; }
        std::set<ComponentType> getNeededComponents() const { return m_needed; }
        Manager *getManager() { return m_manager; }
        virtual bool addEntity(Entity e);
        virtual bool removeEntity(Entity e);
        virtual void init() {}
        virtual void update(float deltaTime);
        virtual void preUpdate(float deltaTime) {}
        virtual void postUpdate(float deltaTime) {}
        virtual void updateEntity(float deltaTime, Entity e) {}
        const std::set<Entity> getEntities() const { return m_entities; }

    private:
        const int m_priority;
        const std::set<ComponentType> m_needed;
        Manager *const m_manager;
        std::set<Entity> m_entities;
    };
}