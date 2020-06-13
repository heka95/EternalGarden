#include "Entity.hpp"

Entity::Entity(unsigned long uniqueId) : m_id(uniqueId)
{
    m_components = {};
}

unsigned long Entity::getId()
{
    return m_id;
}

void Entity::addComponent(BaseComponent *component)
{
    m_components.push_back(component);
}

std::vector<BaseComponent*> Entity::getComponents() const
{
    return m_components;
}