#pragma once
#include <map>
#include <set>
#include "ECSTypes.hpp"
#include "components/BaseComponent.hpp"

namespace Garden
{
    class Store
    {
    public:
        bool hasEntity(Entity entity);
        BaseComponent *getComponent(Entity entity);
        bool add(Entity entity, BaseComponent *component);
        bool remove(Entity entity);
        std::set<Entity> getEntities() const;

    private:
        template <typename T>
        friend class ComponentStore;
        std::map<Entity, BaseComponent *> m_store;
    };
} // namespace Garden