#pragma once
#include <vector>
#include "components/World.hpp"
#include "Vector2D.hpp"

namespace Garden::Core
{
    struct WorldCollisionResult
    {
        bool topLeft{false};
        bool topCenter{false};
        bool topRight{false};
        bool centerLeft{false};
        bool centerRight{false};
        bool bottomRight{false};
        bool bottomCenter{false};
        bool bottomLeft{false};

        bool bottomCollision() { return (bottomRight || bottomCenter || bottomLeft); }
        bool topCollision() { return (topLeft || topCenter || topRight); }
        bool centerCollision() { return (centerLeft || centerRight); }

        int bestLeftPosition{-1};
        int bestRightPosition{-1};
        int bestTopPosition{-1};
        int bestBottomPosition{-1};
    };

    struct PointMapPosition
    {
        int row{-1};
        int column{-1};
        int absolute{-1};
    };

    struct TestingPoints
    {
        PointMapPosition topLeft;
        PointMapPosition topCenter;
        PointMapPosition topRight;
        PointMapPosition centerLeft;
        PointMapPosition centerRight;
        PointMapPosition bottomRight;
        PointMapPosition bottomCenter;
        PointMapPosition bottomLeft;
    };

    class CollisionEngine
    {
    public:
        CollisionEngine(Garden::Components::World *world);
        bool checkCollision(SDL_Rect a, SDL_Rect b);
        WorldCollisionResult worldCollision(SDL_Rect a);
        bool checkXCollision(SDL_Rect a, SDL_Rect b);
        bool checkYCollision(SDL_Rect a, SDL_Rect b);
        PointMapPosition mapPositionFromPoint(int x, int y);

    private:
        TestingPoints mapTestingPointsFromCollider(SDL_Rect a);
        Garden::Components::Layer *m_layerTileMap;
        int m_tileSize{0};
        int m_columns{0};
        int m_row{0};
    };
} // namespace Garden::Core