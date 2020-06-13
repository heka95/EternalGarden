#include "World.hpp"

World::World() : m_layerCounter(0)
{
    m_layers = {};
}

std::vector<Layer*> World::getLayers() const
{
    return m_layers;
}

void World::addLayer(Layer *layer)
{
    m_layers.push_back(layer);
    m_layerCounter++;
}
