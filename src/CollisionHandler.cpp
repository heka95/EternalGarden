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

CollisionHandler::CollisionHandler()
{
    m_collisionLayer = (TileLayer *)GameEngine::getInstance().getWorld()->getLayers().front();
    m_layerTileMap = m_collisionLayer->getTileMap();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b)
{
    bool isXIntersect = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool isYIntersect = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (isXIntersect && isYIntersect);
}

bool CollisionHandler::worldCollision(SDL_Rect a)
{
    int tileSize = 128;
    int rows = 7;
    int columns = 18;

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;
    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if (left_tile < 0)
        left_tile = 0;
    if (right_tile > columns)
        right_tile = columns;
    if (top_tile < 0)
        top_tile = 0;
    if (bottom_tile > rows)
        bottom_tile = rows;

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