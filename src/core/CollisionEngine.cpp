#include "core/CollisionEngine.hpp"
#include <iostream>
#include <algorithm>

namespace Garden::Core
{
    CollisionEngine::CollisionEngine(Garden::Components::World *world)
    {
        m_layerTileMap = world->tileMapLayers[world->physicLayer];
        m_tileSize = world->tileWidth; // or heigth, the grid will always a square
        m_columns = world->columns;
        m_row = world->rows;
    }

    bool CollisionEngine::checkCollision(SDL_Rect a, SDL_Rect b)
    {
        bool isXIntersect = (a.x < b.x + b.w) && (a.x + a.w > b.x);
        bool isYIntersect = (a.y < b.y + b.h) && (a.y + a.h > b.y);
        return (isXIntersect && isYIntersect);
    }

    bool CollisionEngine::worldCollision(SDL_Rect a)
    {
        int left_tile = a.x / m_tileSize;
        int right_tile = (a.x + a.w) / m_tileSize;
        int top_tile = a.y / m_tileSize;
        int bottom_tile = (a.y + a.h) / m_tileSize;

        left_tile = std::max(left_tile, 0);
        top_tile = std::max(top_tile, 0);

        right_tile = std::min(right_tile, m_columns);
        bottom_tile = std::min(bottom_tile, m_row);
        
        bool isCollided{false};

        for (int row = top_tile; row <= bottom_tile; ++row)
        {
            int rowIndex = row * m_columns;
            for (int column = left_tile; column <= right_tile; ++column)
            {
                auto currentTile = m_layerTileMap->tiles[rowIndex + column];
                if (currentTile->TileId > 0)
                {
                    currentTile->isCollided = true;
                    isCollided = true;
                }
            }
        }
        return isCollided;
    }

} // namespace Garden::Core