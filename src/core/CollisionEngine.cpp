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
        bool isXIntersect = checkXCollision(a, b);
        bool isYIntersect = checkYCollision(a, b);
        return (isXIntersect && isYIntersect);
    }

    bool CollisionEngine::checkXCollision(SDL_Rect a, SDL_Rect b)
    {
        return (a.x < b.x + b.w) && (a.x + a.w > b.x);
    }

    bool CollisionEngine::checkYCollision(SDL_Rect a, SDL_Rect b)
    {
        return (a.y < b.y + b.h) && (a.y + a.h > b.y);
    }

    PointMapPosition CollisionEngine::mapPositionFromPoint(int x, int y)
    {
        PointMapPosition position;
        position.column = x / m_tileSize;
        position.row = y / m_tileSize;
        position.absolute = (position.row * m_columns) + position.column;
        return position;
    }

    TestingPoints CollisionEngine::mapTestingPointsFromCollider(SDL_Rect a)
    {
        TestingPoints test;
        test.topLeft = mapPositionFromPoint(a.x, a.y);
        test.topRight = mapPositionFromPoint(a.x + a.w, a.y);
        test.topCenter = mapPositionFromPoint(a.x + (a.w / 2), a.y);

        test.bottomLeft = mapPositionFromPoint(a.x, a.y + a.h);
        test.bottomRight = mapPositionFromPoint(a.x + a.w, a.y + a.h);
        test.bottomCenter = mapPositionFromPoint(a.x + (a.w / 2), a.y + a.h);

        test.centerLeft = mapPositionFromPoint(a.x, a.y + (a.h / 2));
        test.centerRight = mapPositionFromPoint(a.x + a.w, a.y + (a.h / 2));
        return test;
    }

    WorldCollisionResult CollisionEngine::worldCollision(SDL_Rect a)
    {
        WorldCollisionResult result;
        auto test = mapTestingPointsFromCollider(a);

        for (int row = test.topCenter.row; row <= test.bottomCenter.row; ++row)
        {
            int rowIndex = row * m_columns;
            for (int column = test.centerLeft.column; column <= test.centerRight.column; ++column)
            {
                int absolute = rowIndex + column;
                auto testTile = m_layerTileMap->tiles[absolute];
                if (testTile->TileId != 0)
                {
                    testTile->isCollided = true;
                    result.topLeft = !result.topLeft ? (test.topLeft.absolute == absolute) : true;
                    result.topCenter = !result.topCenter ? (test.topCenter.absolute == absolute) : true;
                    result.topRight = !result.topRight ? (test.topRight.absolute == absolute) : true;

                    result.bottomRight = !result.bottomRight ? (test.bottomRight.absolute == absolute) : true;
                    result.bottomCenter = !result.bottomCenter ? (test.bottomCenter.absolute == absolute) : true;
                    result.bottomLeft = !result.bottomLeft ? (test.bottomLeft.absolute == absolute) : true;

                    result.centerLeft = !result.centerLeft ? (test.centerLeft.absolute == absolute) : true;
                    result.centerRight = !result.centerRight ? (test.centerRight.absolute == absolute) : true;
                }
            }
        }

        return result;
    } // namespace Garden::Core

} // namespace Garden::Core