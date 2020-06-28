#pragma once
#include <vector>
#include "components/World.hpp"

namespace Garden::Core
{
    class CollisionEngine
    {
    public:
        CollisionEngine(Garden::Components::World *world);
        bool checkCollision(SDL_Rect a, SDL_Rect b);
        bool worldCollision(SDL_Rect a);

    private:
        std::vector<Garden::Components::Tile> m_layerTileMap;
        int m_tileSize{0};
        int m_columns{0};
        int m_row{0};
    };
} // namespace Garden::Core