#include "core/TextureStore.hpp"
#include <iostream>
#include <fstream>
#include "SDL_image.h"

namespace Garden::Core
{
    TextureStore::TextureStore(SDL_Renderer *sdlRenderer)
    {
        m_renderer = sdlRenderer;
    }

    bool TextureStore::load(std::string id, std::string fileName)
    {
        std::size_t found = fileName.find(".gif");
        if (found != std::string::npos)
        {
            std::cout << "[TEXTURE] [ERROR] can't load GIF texture: " << fileName << " | " << SDL_GetError() << std::endl;
            return false;
        }

        std::ifstream infile{fileName};
        if (!infile.good())
        {
            std::cout << "[TEXTURE] [ERROR] file not exists: " << fileName << " | " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_Surface *surface = IMG_Load(fileName.c_str());
        if (surface == nullptr)
        {
            std::cout << "[TEXTURE] [ERROR] can't load texture: " << fileName << " | " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (texture == nullptr)
        {
            std::cout << "[TEXTURE] [ERROR] can't create texture: " << fileName << " | " << SDL_GetError() << std::endl;
            return false;
        }

        m_textures[id] = texture;
        std::cout << "[TEXTURE] [LOAD]  " << id << "(" << fileName << ")" << std::endl;
        return true;
    }

    void TextureStore::release()
    {
        for (const auto &[key, value] : m_textures)
        {
            std::cout << "[TEXTURE] [UNLOAD]    " << key << std::endl;
            SDL_DestroyTexture(value);
        }
        m_textures.clear();
    }
} // namespace Garden::Core