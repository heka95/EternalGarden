#pragma once

#include <vector>
#include "Layer.hpp"

class World
{
public:
    World();
    std::vector<Layer*> getLayers() const;
    void addLayer(Layer *layer);

private:
    std::vector<Layer*> m_layers;
    unsigned int m_layerCounter;
};