#pragma once
#include <memory>
#include <string>
#include <map>
#include "SDL.h"

namespace Garden::Core
{
    class TextureStore
    {
        public:
        TextureStore(SDL_Renderer *sdlRenderer);
        virtual ~TextureStore() = default;
        bool load(std::string id, std::string fileName);
        void release();
        SDL_Texture *getTextureFromId(const std::string id) { return m_textures[id]; }

        private:
        std::map<std::string, SDL_Texture *> m_textures;
        SDL_Renderer *m_renderer;
    };
} // namespace Garden::Core