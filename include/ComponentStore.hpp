#pragma once
#include "Store.hpp"

namespace Garden
{
    template <typename T>
    class ComponentStore
    {
        static_assert(std::is_base_of<Component, T>::value, "Only Component can be defined");

    public:
        ComponentStore(Store *store) : m_store(store) {}
        bool hasEntity(Entity entity) { return m_store->hasEntity(entity); }
        T *getComponent(Entity entity) { return static_cast<T *>(m_store->getComponent(entity)); }
        bool add(Entity entity, Component *component) { return m_store->add(entity, component); }
        bool remove(Entity entity) { return m_store->remove(entity); }

    private:
        Store *const m_store;
    };
}