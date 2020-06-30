#include "core/CollisionEngine.hpp"
#include <iostream>

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

        if (left_tile < 0)
            left_tile = 0;
        if (right_tile > m_columns)
            right_tile = m_columns;
        if (top_tile < 0)
            top_tile = 0;
        if (bottom_tile > m_row)
            bottom_tile = m_row;

        bool isCollided{false};
        for (int i = top_tile; i <= bottom_tile; ++i)
        {
            for (int j = left_tile; j <= right_tile; ++j)
            {
                auto currentTile = m_layerTileMap->tiles[((i * m_columns) + j)];
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