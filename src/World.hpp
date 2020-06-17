#pragma once

#include <vector>
#include "Layer.hpp"

class World
{
public:
    World() = default;
    void render();
    void update();
    void release();
    std::vector<Layer *> getLayers();

private:
    friend class MapLoader;
    std::vector<Layer *> m_layers;
};