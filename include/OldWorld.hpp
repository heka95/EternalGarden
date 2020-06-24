#pragma once

#include <vector>
#include "Layer.hpp"

class OldWorld
{
public:
    OldWorld() = default;
    void render();
    void update();
    void release();
    std::vector<Layer *> getLayers();

private:
    friend class MapLoader;
    std::vector<Layer *> m_layers;
};