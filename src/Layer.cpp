#include "Layer.hpp"

Layer::Layer() : m_counter(0)
{ 
    m_entityList = {};
}

void Layer::addEntity(Entity *entity)
{
    m_entityList.push_back(entity);
    m_counter++;
}

std::vector<Entity*> Layer::getEntities() const
{
    return m_entityList;
}