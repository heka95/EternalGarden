#include "TextureManager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "GameEngine.hpp"

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

void TextureManager::draw(std::string id, Garden::Vector2D position, Garden::Size size)
{
    SDL_Rect sourceRect = {0, 0, size.width, size.height};
    SDL_Rect destinationRest = {position.x, position.y, size.width, size.height};
    SDL_RenderCopyEx(GameEngine::getInstance().getRenderer(), m_textures[id], &sourceRect, &destinationRest, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::unload(std::string id)
{
    SDL_DestroyTexture(m_textures[id]);
    m_textures.erase(id);
}

void TextureManager::release()
{
    for (const auto& [key, value] : m_textures)
    {
        SDL_DestroyTexture(value);
    }
    m_textures.clear();
}