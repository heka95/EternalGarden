#include "CollisionHandler.hpp"

std::unique_ptr<CollisionHandler> CollisionHandler::m_instance;
CollisionHandler &CollisionHandler::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new CollisionHandler());
    }
    return *m_instance.get();
}

void CollisionHandler::setCollisionMap(std::vector<std::vector<int>> tileMap, int tileSize)
{
    m_layerTileMap = tileMap;
    m_tileSize = tileSize;
    m_tileHeight = tileMap.size();
    m_tileWidth = tileMap[0].size();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b)
{
    bool isXIntersect = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool isYIntersect = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (isXIntersect && isYIntersect);
}

bool CollisionHandler::worldCollision(SDL_Rect a)
{
    int left_tile = a.x / m_tileSize;
    int right_tile = (a.x + a.w) / m_tileSize;
    int top_tile = a.y / m_tileSize;
    int bottom_tile = (a.y + a.h) / m_tileSize;

    if (left_tile < 0)
        left_tile = 0;
    if (right_tile > m_tileWidth)
        right_tile = m_tileWidth;
    if (top_tile < 0)
        top_tile = 0;
    if (bottom_tile > m_tileHeight)
        bottom_tile = m_tileHeight;

    for (int i = left_tile; i <= right_tile; ++i)
    {
        for (int j = top_tile; j <= bottom_tile; ++j)
        {
            if (m_layerTileMap[j][i] > 0)
            {
                return true;
            }
        }
    }
    return false;
}