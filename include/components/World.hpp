#pragma once

#include <vector>
#include <map>
#include "core/ECSTypes.hpp"
#include "BaseComponent.hpp"

namespace Garden::Components
{
    class TileSet
    {
    public:
        TileSet() = default;
        int FirstId = 0;
        int LastId = 0;
        int Rows = 0;
        int Columns = 0;
        int TileCount = 0;
        int TileSize = 0;
        std::string Name = "";
        std::string Source = "";
    };

    class World
    {
    public:
        int rows = 0;
        int columns = 0;
        int tileWidth = 0;
        int tileHeight = 0;
        std::vector<TileSet> tileSets;
        std::map<std::string, std::vector<int>> tileMapLayers;
        std::string physicLayer = "";
    };
} // namespace Garden::Components