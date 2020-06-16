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
    bool parseTextures(std::string sourcePath);
    void unload(std::string id);
    void release();
    void draw(std::string id, Garden::Vector2I position, Garden::Size size, Garden::Vector2F scale = Garden::Vector2F{1, 1}, float scrollFactor = 0, Garden::Flip renderFlip = Garden::Flip::NONE);
    void drawFrame(std::string id, Garden::Vector2I position, Garden::Size size, int row, int frame, Garden::Flip renderFlip = Garden::Flip::NONE);
    void drawTile(std::string tileSetId, int tileSize, Garden::Vector2I position, int row, int frame, Garden::Flip renderFlip = Garden::Flip::NONE);

private:
    TextureManager() = default;
    TextureManager(const TextureManager &object) = delete;
    TextureManager &operator=(const TextureManager &object) = delete;
    static std::unique_ptr<TextureManager> m_instance;
    std::map<std::string, SDL_Texture *> m_textures;
};