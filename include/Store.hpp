#pragma once
#include <map>
#include <set>
#include "core/ECSTypes.hpp"
#include "Component.hpp"

namespace Garden
{
    class Store
    {
    public:
        bool hasEntity(Entity entity);
        Component *getComponent(Entity entity);
        bool add(Entity entity, Component *component);
        bool remove(Entity entity);
        std::set<Entity> getEntities() const;

    private:
        template <typename T>
        friend class ComponentStore;
        std::map<Entity, Component *> m_store;
    };
} // namespace Garden