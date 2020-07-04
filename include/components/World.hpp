#pragma once

#include <vector>
#include "SDL.h"
#include "core/ECSTypes.hpp"
#include "BaseComponent.hpp"
#include "core/WorldObjectDefinition.hpp"

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

    class Tile
    {
        public:
        int TileId{0};
        SDL_RendererFlip flip{SDL_RendererFlip::SDL_FLIP_NONE};
        bool isCollided{false};
    };

    class Layer
    {
        public:
        std::vector<Tile*> tiles;
        std::string name{""};
        bool isCollider{false};
    };

    class World
    {
    public:
        World() = default;
        int rows = 0;
        int columns = 0;
        int tileWidth = 0;
        int tileHeight = 0;
        std::vector<TileSet> tileSets;
        std::vector<Entity> backgrounds;
        std::vector<Layer*> tileMapLayers;
        std::vector<Garden::Core::WorldObjectDefinition> entities;
        int physicLayer = {-1};
        int emptyTile{0};
        bool debug{false};

        int getTileSetIndexFromTileId(int tileId)
        {
            if (tileSets.size() == 1)
            {
                return tileId;
            }
            if (tileSets.size() > 1)
            {
                for (unsigned int k = 0; k < tileSets.size(); k++)
                {
                    if (tileId >= tileSets[k].FirstId && tileId <= tileSets[k].LastId)
                    {
                        return k;
                        break;
                    }
                }
            }
            return -1;
        }
    };
} // namespace Garden::Components