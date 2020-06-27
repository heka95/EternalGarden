#pragma once
#include "SDL.h"
#include "core/Manager.hpp"
#include "core/LuaAccessor.hpp"
#include "components/World.hpp"
#include "core/TextureStore.hpp"

namespace Garden::Managers
{
    class GameManager : public Garden::Manager
    {
    public:
        GameManager(SDL_Renderer *sdlRenderer);
        ~GameManager();
        void load(SDL_Renderer *sdlRenderer);
        bool enable() const { return m_isEnable; }
        void enable(const bool &enable) { m_isEnable = enable; }

    private:
        bool m_isEnable = false;
        Garden::Core::LuaAccessor *m_lua;
        Garden::Components::World *m_world;
        Garden::Core::TextureStore *m_textureStore;
    };
} // namespace Garden::Managers