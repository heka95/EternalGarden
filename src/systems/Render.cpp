#include "systems/Render.hpp"
#include "OldTextureManager.hpp"
#include "core/Manager.hpp"
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
        auto cTransform = getManager()->getComponent<Garden::Components::Transform>(e);
        auto position = cTransform->Position;

        auto cRenderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);
        auto cameraPosition = m_camera->position;

        SDL_Rect sourceRect = {(int)cRenderer->drawOffset.X, (int)cRenderer->drawOffset.Y, cRenderer->drawWidth, cRenderer->drawHeight};
        auto renderWidth = cRenderer->drawWidth * cRenderer->scale.X;
        auto renderHeight = cRenderer->drawHeight * cRenderer->scale.Y;
        SDL_FRect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, renderWidth, renderHeight};
        auto texture = m_store->getTextureFromId(cRenderer->textureId);
        SDL_RenderCopyExF(m_renderer, texture, &sourceRect, &destinationRect, cRenderer->rotation, nullptr, cRenderer->flip);
    }

    void Render::drawMap()
    {
        int renderPrecache = 2;

        auto cameraPosition = m_camera->position;
        auto minI = static_cast<int>(cameraPosition.Y) / m_world->tileHeight;
        auto maxI = (minI + (static_cast<int>(m_camera->viewBox.h) / m_world->tileHeight)) + renderPrecache;
        if (maxI > m_world->rows)
            maxI = m_world->rows;

        auto minJ = static_cast<int>(cameraPosition.X) / m_world->tileWidth;
        auto maxJ = (minJ + (static_cast<int>(m_camera->viewBox.w) / m_world->tileWidth)) + renderPrecache;
        if (maxJ > m_world->columns)
            maxJ = m_world->columns;

        int drawedTiles = 0;

        for (auto &key : m_world->tileMapLayers)
        {
            for (int i = minI; i < maxI; i++)
            {
                for (int j = minJ; j < maxJ; j++)
                {
                    drawedTiles++;
                    auto currentTile = key.at((i * m_world->columns) + j);
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

                    auto position = Garden::Vector2D{j * tileSet.TileSize, i * tileSet.TileSize};
                    SDL_Rect sourceRect = {tileSet.TileSize * tileColumn, tileSet.TileSize * tileRow, tileSet.TileSize, tileSet.TileSize};
                    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, tileSet.TileSize, tileSet.TileSize};
                    auto texture = m_store->getTextureFromId(tileSet.Name);
                    SDL_RenderCopyEx(m_renderer, texture, &sourceRect, &destinationRect, 0, nullptr, currentTile.flip);
                }
            }
        }

        //std::cout << "drawed tiles: " << drawedTiles << std::endl;
    }

} // namespace Garden::Systems