#include "Store.hpp"

namespace Garden
{
    bool Store::hasEntity(Entity e)
    {
        auto it = m_store.find(e);
        return it != m_store.end();
    }

    BaseComponent *Store::getComponent(Entity e)
    {
        auto it = m_store.find(e);
        return (it == m_store.end() ? nullptr : it->second);
    }

    bool Store::add(Entity e, BaseComponent *c)
    {
        auto ret = m_store.insert(std::make_pair(e, c));
        return ret.second;
    }

    bool Store::remove(Entity e)
    {
        auto count = m_store.erase(e);
        return count > 0;
    }

    std::set<Entity> Store::getEntities() const
    {
        std::set<Entity> ret;

        for (auto elt : m_store)
        {
            ret.insert(elt.first);
        }

        return ret;
    }
} // namespace Garden