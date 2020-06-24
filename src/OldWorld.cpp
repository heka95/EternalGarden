#include "OldWorld.hpp"

void OldWorld::render()
{
    for (auto *layer : m_layers)
    {
        layer->render();
    }
}

void OldWorld::update()
{
    for (auto *layer : m_layers)
    {
        layer->update();
    }
}

std::vector<Layer *> OldWorld::getLayers()
{
    return m_layers;
}

void OldWorld::release()
{
    for (auto layer : m_layers)
    {
        delete layer;
    }
    m_layers.clear();
}