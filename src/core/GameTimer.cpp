#include "core/GameTimer.hpp"
#include "SDL.h"
#include <iostream>

namespace Garden::Core
{
    GameTimer::GameTimer()
    {
        m_lastTime = SDL_GetTicks();
    }

    void GameTimer::update()
    {
        m_deltaTime = (SDL_GetTicks() - m_lastTime);

        if (m_deltaTime > m_frameTime)
        {
            m_deltaTime = m_frameTime;
        }
        if(m_deltaTime < m_frameTime)
        {
            SDL_Delay(m_frameTime - m_deltaTime);
            m_deltaTime = (SDL_GetTicks() - m_lastTime);
        }
        //m_deltaTime *= m_factor;

        m_lastTime = SDL_GetTicks();
    }
} // namespace Garden::Core