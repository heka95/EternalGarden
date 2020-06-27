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

    class World : public Garden::BaseComponent
    {
    public:
        static const ComponentType type = Garden::Types::WorldType;
        World()
        {
            m_type = type;
        }
        int rows = 0;
        int columns = 0;
        int tileWidth = 0;
        int tileHeight = 0;
        std::vector<TileSet> tileSets;
        std::map<std::string, std::vector<int>> tileMapLayers;
        std::string physicLayer = "";
        int emptyTile{0};

        int getTileSetIndexFromTileId(int tileId)
        {
            int tileSetIndex = 0;
            if (tileSets.size() > 1)
            {
                for (unsigned int k = 1; k < tileSets.size(); k++)
                {
                    if (tileId > tileSets[k].FirstId && tileId < tileSets[k].LastId)
                    {
                        tileId = tileId + tileSets[k].TileCount - tileSets[k].LastId;
                        tileSetIndex = k;
                        break;
                    }
                }
            }
            return tileSetIndex;
        }
    };
} // namespace Garden::Components