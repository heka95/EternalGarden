#pragma once
#include "core/Manager.hpp"
#include "SDL.h"

namespace Garden::Managers
{
    class GameManager : public Garden::Manager
    {
    public:
        GameManager(SDL_Renderer *sdlRenderer);
        void load(SDL_Renderer *sdlRenderer);
        bool enable() const { return m_isEnable; }
        void enable(const bool &enable) { m_isEnable = enable; }

    private:
        bool m_isEnable = false;
    };
} // namespace Garden::Managers