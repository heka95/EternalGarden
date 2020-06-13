#pragma once

#include <memory>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include "Types/GameTypes.hpp"

class TextureManager
{
public:
    virtual ~TextureManager() = default;
    static TextureManager &getInstance();
    bool load(std::string id, std::string fileName);
    void unload(std::string id);
    void release();
    void draw(std::string id, Garden::Vector2I position, Garden::Size size, Garden::Flip renderFlip = Garden::Flip::NONE);
    void drawFrame(std::string id, Garden::Vector2I position, Garden::Size size, int row, int frame, Garden::Flip renderFlip = Garden::Flip::NONE);

private:
    TextureManager() = default;
    TextureManager(const TextureManager &object) = delete;
    TextureManager &operator=(const TextureManager &object) = delete;
    static std::unique_ptr<TextureManager> m_instance;
    std::map<std::string, SDL_Texture*> m_textures;
};