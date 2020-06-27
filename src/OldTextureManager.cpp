#include "OldTextureManager.hpp"
#include <iostream>
#include <fstream>
#include <iostream>
#include "SDL_image.h"
#include "GameEngine.hpp"
#include "Camera.hpp"
#include "json.hpp"

std::unique_ptr<OldTextureManager> OldTextureManager::m_instance;
OldTextureManager &OldTextureManager::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new OldTextureManager());
    }
    return *m_instance.get();
}

bool OldTextureManager::load(std::string id, std::string fileName)
{
    SDL_Surface *surface = IMG_Load(fileName.c_str());
    if (surface == nullptr)
    {
        std::cout << "Can't load texture: " << fileName << " | " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(GameEngine::getInstance().getRenderer(), surface);
    if (texture == nullptr)
    {
        std::cout << "Can't create texture from surface: " << fileName << " | " << SDL_GetError() << std::endl;
        return false;
    }

    m_textures[id] = texture;
    std::cout << "Load Texture ID:" << id << " | " << fileName << " Generated" << std::endl;
    return true;
}

bool OldTextureManager::parseTextures(std::string sourcePath)
{
    std::ifstream file_input(sourcePath.c_str(), std::ios::in);
    if (file_input.fail())
    {
        std::cout << "Can't load the file " << sourcePath << std::endl;
        return false;
    }
    nlohmann::json jsonData{};
    file_input >> jsonData;

    for (auto &texture : jsonData["textures"])
    {
        if (!load(texture["id"], texture["file"]))
        {
            return false;
        }
    }

    return true;
}

void OldTextureManager::draw(std::string id, Garden::Vector2I position, Garden::Size size, Garden::Vector2F scale, Garden::Flip renderFlip, float speedRatio, float rotation)
{
    SDL_Rect sourceRect = {0, 0, size.width, size.height};

    auto cameraPosition = Camera::getInstance().getPosition() * speedRatio;
    auto xRect = size.width * scale.X;
    auto yRect = size.height * scale.Y;
    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, (int)xRect, (int)yRect};

    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[id], &sourceRect, &destinationRect, rotation, nullptr, static_cast<SDL_RendererFlip>(renderFlip));
}

void OldTextureManager::drawFrame(std::string id, Garden::Vector2I position, Garden::Size size, int row, int frame, Garden::Flip renderFlip, Garden::Vector2F scale, float speedRatio, float rotation)
{
    SDL_Rect sourceRect = {size.width * frame, size.height * (row - 1), size.width, size.height};

    auto cameraPosition = Camera::getInstance().getPosition() * speedRatio;
    auto xRect = size.width * scale.X;
    auto yRect = size.height * scale.Y;
    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, (int)xRect, (int)yRect};
    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[id], &sourceRect, &destinationRect, rotation, nullptr, static_cast<SDL_RendererFlip>(renderFlip));
}

void OldTextureManager::drawTile(std::string tileSetId, int tileSize, Garden::Vector2I position, int row, int frame, Garden::Flip renderFlip, float speedRatio)
{
    auto cameraPosition = Camera::getInstance().getPosition() * speedRatio;
    SDL_Rect sourceRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, tileSize, tileSize};
    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[tileSetId], &sourceRect, &destinationRect, 0, nullptr, static_cast<SDL_RendererFlip>(renderFlip));
}

void OldTextureManager::unload(std::string id)
{
    std::cout << "Delete Texture ID:" << id << std::endl;
    SDL_DestroyTexture(m_textures[id]);
    m_textures.erase(id);
}

void OldTextureManager::release()
{
    for (const auto &[key, value] : m_textures)
    {
        std::cout << "Delete Texture ID:" << key << std::endl;
        SDL_DestroyTexture(value);
    }
    m_textures.clear();
}