#pragma once

#include <memory>
#include <string>
#include <map>
#include "SDL.h"
#include "GameTypes.hpp"

class OldTextureManager
{
public:
    virtual ~OldTextureManager() = default;
    static OldTextureManager &getInstance();
    bool load(std::string id, std::string fileName);
    bool parseTextures(std::string sourcePath);
    void unload(std::string id);
    void release();
    void draw(std::string id, Garden::Vector2I position, Garden::Size size, Garden::Vector2F scale = Garden::Vector2F{1, 1}, Garden::Flip renderFlip = Garden::Flip::NONE, float speedRatio = 1.0f, float rotation = 0.0f);
    void drawFrame(std::string id, Garden::Vector2I position, Garden::Size size, int row, int frame, Garden::Flip renderFlip = Garden::Flip::NONE, Garden::Vector2F scale = Garden::Vector2F{1, 1}, float speedRatio = 1.0f, float rotation = 0.0f);
    void drawTile(std::string tileSetId, int tileSize, Garden::Vector2I position, int row, int frame, Garden::Flip renderFlip = Garden::Flip::NONE, float speedRatio = 1.0f);
    SDL_Texture *getTextureFromId(std::string id) { return m_textures[id]; }

private:
    OldTextureManager() = default;
    OldTextureManager(const OldTextureManager &object) = delete;
    OldTextureManager &operator=(const OldTextureManager &object) = delete;
    static std::unique_ptr<OldTextureManager> m_instance;
    std::map<std::string, SDL_Texture *> m_textures;
};