#pragma once

#include <memory>
#include "SDL.h"
#include <vector>
#include "TileLayer.hpp"
#include "GameEngine.hpp"

class CollisionHandler
{
public:
    virtual ~CollisionHandler() = default;
    static CollisionHandler &getInstance();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool worldCollision(SDL_Rect a);
    void setCollisionMap(std::vector<std::vector<int>> tileMap, int tileSize);

private:
    CollisionHandler() = default;
    CollisionHandler(const CollisionHandler &object) = delete;
    CollisionHandler &operator=(const CollisionHandler &object) = delete;
    static std::unique_ptr<CollisionHandler> m_instance;
    std::vector<std::vector<int>> m_layerTileMap;
    int m_tileSize;
    int m_tileHeight;
    int m_tileWidth;
};