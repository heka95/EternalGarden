#include "core/GameTimer.hpp"
#include "SDL.h"

namespace Garden::Core
{
    GameTimer::GameTimer()
    {
        reset();
    }

    void GameTimer::reset()
    {
        m_startTick = SDL_GetTicks();
        m_elapsedTick = 0;
        m_deltaTime = 0.0f;
    }

    void GameTimer::update()
    {
        m_elapsedTick = SDL_GetTicks() - m_startTick;
        m_deltaTime = m_elapsedTick * 0.001f;
    }
} // namespace Garden::Core