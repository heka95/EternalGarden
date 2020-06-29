#include "systems/Render.hpp"
#include "OldTextureManager.hpp"
#include "core/Manager.hpp"
#include "components/SpriteAnimation.hpp"
#include <iostream>

namespace Garden::Systems
{
    void Render::preUpdate(float delta)
    {
        SDL_SetRenderDrawColor(m_renderer, 0x2B, 0x84, 0xAB, 0xFF);
        SDL_RenderClear(m_renderer);
        if (m_world != nullptr)
        {
            drawMap();
        }
    }

    void Render::postUpdate(float delta)
    {
        SDL_RenderPresent(m_renderer);
    }

    void Render::updateEntity(float deltaTime, Entity e)
    {
        auto transform = getManager()->getComponent<Garden::Components::Transform>(e);
        auto position = transform->Position;
        auto cameraPosition = m_camera->position;

        auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        SDL_Rect sourceRect = {(int)renderer->drawOffset.X, (int)renderer->drawOffset.Y, renderer->drawWidth, renderer->drawHeight};
        auto renderWidth = renderer->drawWidth * renderer->scale.X;
        auto renderHeight = renderer->drawHeight * renderer->scale.Y;
        SDL_FRect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, renderWidth, renderHeight};
        auto texture = m_store->getTextureFromId(renderer->textureId);
        SDL_RenderCopyExF(m_renderer, texture, &sourceRect, &destinationRect, renderer->rotation, nullptr, renderer->flip);
    }

    void Render::drawMap()
    {
        int renderPrecache = 2;

        auto cameraPosition = m_camera->position;
        auto minI = static_cast<int>(cameraPosition.Y) / m_world->tileHeight;
        auto maxI = (minI + (static_cast<int>(m_camera->viewBox.h) / m_world->tileHeight)) + renderPrecache;
        if (maxI > m_world->rows)
            maxI = m_world->rows;
        if (minI < 0)
            minI = 0;

        auto minJ = static_cast<int>(cameraPosition.X) / m_world->tileWidth;
        auto maxJ = (minJ + (static_cast<int>(m_camera->viewBox.w) / m_world->tileWidth)) + renderPrecache;
        if (maxJ > m_world->columns)
            maxJ = m_world->columns;
        if (minJ < 0)
            minJ = 0;

        int drawedTiles = 0;

        for (auto &key : m_world->tileMapLayers)
        {
            if(key.isCollider)
            continue;
            for (int i = minI; i < maxI; i++)
            {
                for (int j = minJ; j < maxJ; j++)
                {
                    drawedTiles++;
                    auto currentTile = key.tiles.at((i * m_world->columns) + j);
                    if (currentTile.TileId == m_world->emptyTile)
                    {
                        continue;
                    }
                    int tileSetIndex = m_world->getTileSetIndexFromTileId(currentTile.TileId);
                    if (tileSetIndex == -1)
                    {
                        //std::cerr << "Can't find tileset of tile Number " << tileId << std::endl;
                        continue;
                    }
                    currentTile.TileId = currentTile.TileId + m_world->tileSets[tileSetIndex].TileCount - m_world->tileSets[tileSetIndex].LastId;
                    auto tileSet = m_world->tileSets[tileSetIndex];
                    auto tileRow = currentTile.TileId / tileSet.Columns;
                    auto tileColumn = currentTile.TileId - tileRow * tileSet.Columns - 1;

                    if (currentTile.TileId % tileSet.Columns == 0)
                    {
                        tileRow--;
                        tileColumn = tileSet.Columns - 1;
                    }

                    SDL_Rect sourceRect = {tileSet.TileSize * tileColumn, tileSet.TileSize * tileRow, tileSet.TileSize, tileSet.TileSize};
                    SDL_Rect destinationRect = {static_cast<int>((j * tileSet.TileSize) - cameraPosition.X), static_cast<int>((i * tileSet.TileSize) - cameraPosition.Y), tileSet.TileSize, tileSet.TileSize};
                    auto texture = m_store->getTextureFromId(tileSet.Name);
                    SDL_RenderCopyEx(m_renderer, texture, &sourceRect, &destinationRect, 0, nullptr, currentTile.flip);
                }
            }
        }

        if (m_world->debug)
        {
            auto colliderLayer = m_world->tileMapLayers[m_world->physicLayer];
            for (int i = minI; i < maxI; i++)
            {
                for (int j = minJ; j < maxJ; j++)
                {
                    auto currentTile = colliderLayer.tiles.at((i * m_world->columns) + j);
                    if (currentTile.TileId == m_world->emptyTile)
                    {
                        continue;
                    }
                    int tileSetIndex = m_world->getTileSetIndexFromTileId(currentTile.TileId);
                    if (tileSetIndex == -1)
                    {
                        //std::cerr << "Can't find tileset of tile Number " << tileId << std::endl;
                        continue;
                    }
                    currentTile.TileId = currentTile.TileId + m_world->tileSets[tileSetIndex].TileCount - m_world->tileSets[tileSetIndex].LastId;
                    auto tileSet = m_world->tileSets[tileSetIndex];
                    auto tileRow = currentTile.TileId / tileSet.Columns;

                    if (currentTile.TileId % tileSet.Columns == 0)
                    {
                        tileRow--;
                    }

                    SDL_Rect destinationRect = {static_cast<int>((j * tileSet.TileSize) - cameraPosition.X), static_cast<int>((i * tileSet.TileSize) - cameraPosition.Y), tileSet.TileSize, tileSet.TileSize};
                    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
                    SDL_RenderDrawRect(m_renderer, &destinationRect);
                }
            }
        }
    }
} // namespace Garden::Systems