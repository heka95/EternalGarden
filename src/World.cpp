#include "World.hpp"

void World::render()
{
    for (auto *layer : m_layers)
    {
        layer->render();
    }
}

void World::update()
{
    for (auto *layer : m_layers)
    {
        layer->update();
    }
}

std::vector<Layer *> World::getLayers()
{
    return m_layers;
}

void World::release()
{
    for (auto layer : m_layers)
    {
        delete layer;
    }
    m_layers.clear();
}