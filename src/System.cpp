#include "System.hpp"

namespace Garden
{
    bool System::addEntity(Entity e)
    {
        auto pairResult = m_entities.insert(e);
        return pairResult.second;
    }

    bool System::removeEntity(Entity e)
    {
        auto erasedElementsCount = m_entities.erase(e);
        return (erasedElementsCount > 0);
    }

    void System::update(float deltaTime)
    {
        for (auto e : getEntities())
        {
            updateEntity(deltaTime, e);
        }
    }

} // namespace Garden