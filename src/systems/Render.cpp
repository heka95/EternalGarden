#include "systems/Render.hpp"
#include "core/Manager.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/RigidBody.hpp"
#include <iostream>
#include <cmath>

namespace Garden::Systems
{
    void Render::preUpdate(float delta)
    {
        SDL_SetRenderDrawColor(m_renderer, 0x2B, 0x84, 0xAB, 0xFF);
        SDL_RenderClear(m_renderer);
    }

    void Render::postUpdate(float delta)
    {
        SDL_RenderPresent(m_renderer);
    }

    void Render::update(float deltaTime)
    {
        if (m_world != nullptr)
        {
            drawBackground();
            drawMap();
        }
        for (auto e : getEntities())
        {
            updateEntity(deltaTime, e);
        }
    }

    void Render::updateEntity(float deltaTime, Entity e)
    {
        auto transform = getManager()->getComponent<Garden::Components::Transform>(e);
        auto position = transform->Position;
        auto cameraViewBox = m_camera->viewBox;

        auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

        SDL_Rect sourceRect = {(renderer->drawOffset.X), (renderer->drawOffset.Y), renderer->drawWidth, renderer->drawHeight};
        auto renderWidth = static_cast<int>(renderer->drawWidth * renderer->scale.X);
        auto renderHeight = static_cast<int>(renderer->drawHeight * renderer->scale.Y);
        SDL_Rect destinationRect;

        destinationRect = {static_cast<int>(position.X - cameraViewBox.x), static_cast<int>(position.Y - cameraViewBox.y), renderWidth, renderHeight};
        auto texture = m_store->getTextureFromId(renderer->textureId);
        SDL_RenderCopyEx(m_renderer, texture, &sourceRect, &destinationRect, renderer->rotation, nullptr, renderer->flip);

        if (m_world->debug)
        {
            auto rigidBody = getManager()->getComponent<Garden::Components::RigidBody>(e);

            SDL_Rect box = {(rigidBody->collider().x - cameraViewBox.x), (rigidBody->collider().y - cameraViewBox.y), rigidBody->collider().w, rigidBody->collider().h};
            SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(m_renderer, &box);
        }
    }

    void Render::drawBackground()
    {
        for (auto e : m_world->backgrounds)
        {
            auto transform = getManager()->getComponent<Garden::Components::Transform>(e);
            auto position = transform->Position;
            auto cameraViewBox = m_camera->viewBox;

            auto renderer = getManager()->getComponent<Garden::Components::SpriteRenderer>(e);

            SDL_Rect sourceRect = {static_cast<int>(renderer->drawOffset.X), static_cast<int>(renderer->drawOffset.Y), renderer->drawWidth, renderer->drawHeight};
            auto renderWidth = static_cast<int>(renderer->drawWidth * renderer->scale.X);
            auto renderHeight = static_cast<int>(renderer->drawHeight * renderer->scale.Y);
            SDL_Rect destinationRect;

            // Change default bottom-left draw to top-left drawing
            auto imageYZeroTop = position.Y - renderer->height;
            auto drawPosition = (imageYZeroTop - cameraViewBox.y);

            destinationRect = {static_cast<int>(position.X - cameraViewBox.x), static_cast<int>(drawPosition), renderWidth, renderHeight};
            auto texture = m_store->getTextureFromId(renderer->textureId);
            SDL_RenderCopyEx(m_renderer, texture, &sourceRect, &destinationRect, renderer->rotation, nullptr, renderer->flip);
        }
    }

    void Render::drawMap()
    {
        int renderPrecache = 2;

        auto cameraViewBox = m_camera->viewBox;
        auto minDrawingRow = static_cast<int>(cameraViewBox.y) / m_world->tileHeight;
        auto maxDrawingRow = (minDrawingRow + (static_cast<int>(m_camera->viewBox.h) / m_world->tileHeight)) + renderPrecache;
        if (maxDrawingRow > m_world->rows)
            maxDrawingRow = m_world->rows;
        if (minDrawingRow < 0)
            minDrawingRow = 0;

        auto minDrawingColumn = static_cast<int>(cameraViewBox.x) / m_world->tileWidth;
        auto maxDrawingColumn = (minDrawingColumn + (static_cast<int>(m_camera->viewBox.w) / m_world->tileWidth)) + renderPrecache;
        if (maxDrawingColumn > m_world->columns)
            maxDrawingColumn = m_world->columns;
        if (minDrawingColumn < 0)
            minDrawingColumn = 0;

        int drawedTiles = 0;

        for (auto &currentLayer : m_world->tileMapLayers)
        {
            for (int row = minDrawingRow; row < maxDrawingRow; row++)
            {
                int rowIndex = row * m_world->columns;
                for (int column = minDrawingColumn; column < maxDrawingColumn; column++)
                {
                    drawedTiles++;
                    auto currentTile = currentLayer->tiles[rowIndex + column];
                    if (currentTile->TileId == m_world->emptyTile)
                    {
                        continue;
                    }
                    int tileSetIndex = m_world->getTileSetIndexFromTileId(currentTile->TileId);
                    if (tileSetIndex == -1)
                    {
                        continue;
                    }
                    auto relativeId = currentTile->TileId + m_world->tileSets[tileSetIndex].TileCount - m_world->tileSets[tileSetIndex].LastId;
                    auto tileSet = m_world->tileSets.at(tileSetIndex);
                    auto tileRow = relativeId / tileSet.Columns;
                    auto tileColumn = relativeId - tileRow * tileSet.Columns - 1;

                    if (relativeId % tileSet.Columns == 0)
                    {
                        tileRow--;
                        tileColumn = tileSet.Columns - 1;
                    }

                    SDL_Rect sourceRect = {tileSet.TileSize * tileColumn, tileSet.TileSize * tileRow, tileSet.TileSize, tileSet.TileSize};
                    SDL_Rect destinationRect = {((column * tileSet.TileSize) - cameraViewBox.x), ((row * tileSet.TileSize) - cameraViewBox.y), tileSet.TileSize, tileSet.TileSize};
                    auto texture = m_store->getTextureFromId(tileSet.Name);
                    SDL_RenderCopyEx(m_renderer, texture, &sourceRect, &destinationRect, 0, nullptr, currentTile->flip);
                    SDL_RenderDrawPoint(m_renderer, destinationRect.x, destinationRect.y);
                }
            }
        }

        if (m_world->debug)
        {
            auto colliderLayer = m_world->tileMapLayers[m_world->physicLayer];
            for (int row = minDrawingRow; row < maxDrawingRow; row++)
            {
                int rowIndex = row * m_world->columns;
                for (int column = minDrawingColumn; column < maxDrawingColumn; column++)
                {
                    auto currentTile = colliderLayer->tiles[rowIndex + column];
                    if (currentTile->TileId == m_world->emptyTile || !currentTile->isCollided)
                    {
                        continue;
                    }
                    currentTile->isCollided = false;
                    int tileSetIndex = m_world->getTileSetIndexFromTileId(currentTile->TileId);
                    if (tileSetIndex == -1)
                    {
                        //std::cerr << "Can't find tileset of tile Number " << tileId << std::endl;
                        continue;
                    }
                    auto relativeId = currentTile->TileId + m_world->tileSets[tileSetIndex].TileCount - m_world->tileSets[tileSetIndex].LastId;
                    auto tileSet = m_world->tileSets.at(tileSetIndex);
                    auto tileRow = relativeId / tileSet.Columns;

                    if (relativeId % tileSet.Columns == 0)
                    {
                        tileRow--;
                    }

                    SDL_Rect destinationRect = {((column * tileSet.TileSize) - cameraViewBox.x), ((row * tileSet.TileSize) - cameraViewBox.y), tileSet.TileSize, tileSet.TileSize};
                    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
                    SDL_RenderDrawRect(m_renderer, &destinationRect);
                }
            }
        }
    }
} // namespace Garden::Systems