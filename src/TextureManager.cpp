#include "TextureManager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "GameEngine.hpp"
#include "Camera.hpp"

std::unique_ptr<TextureManager> TextureManager::m_instance;
TextureManager &TextureManager::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new TextureManager());
    }
    return *m_instance.get();
}

bool TextureManager::load(std::string id, std::string fileName)
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
    std::cout << "Texture ID:" << id << " | " << fileName << " Generated" << std::endl;
    return true;
}

void TextureManager::draw(std::string id, Garden::Vector2I position, Garden::Size size, Garden::Flip renderFlip)
{
    auto cameraPosition = Camera::getInstance().getPosition() * 0.2f;
    SDL_Rect sourceRect = {0, 0, size.width, size.height};
    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, size.width, size.height};
    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[id], &sourceRect, &destinationRect, 0, nullptr, static_cast<SDL_RendererFlip>(renderFlip));
}

void TextureManager::drawFrame(std::string id, Garden::Vector2I position, Garden::Size size, int row, int frame, Garden::Flip renderFlip)
{
    auto cameraPosition = Camera::getInstance().getPosition();
    SDL_Rect sourceRect = {size.width * frame, size.height * (row - 1), size.width, size.height};
    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, size.width, size.height};
    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[id], &sourceRect, &destinationRect, 0, nullptr, static_cast<SDL_RendererFlip>(renderFlip));
}

void TextureManager::drawTile(std::string tileSetId, int tileSize, Garden::Vector2I position, int row, int frame, Garden::Flip renderFlip)
{
    auto cameraPosition = Camera::getInstance().getPosition();
    SDL_Rect sourceRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    SDL_Rect destinationRect = {position.X - cameraPosition.X, position.Y - cameraPosition.Y, tileSize, tileSize};
    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[tileSetId], &sourceRect, &destinationRect, 0, 0, static_cast<SDL_RendererFlip>(renderFlip));
}

void TextureManager::unload(std::string id)
{
    SDL_DestroyTexture(m_textures[id]);
    m_textures.erase(id);
}

void TextureManager::release()
{
    for (const auto &[key, value] : m_textures)
    {
        SDL_DestroyTexture(value);
    }
    m_textures.clear();
}