#include "Timer.hpp"
#include "SDL.h"

std::unique_ptr<Timer> Timer::m_instance;
Timer &Timer::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new Timer());
    }
    return *m_instance.get();
}

void Timer::tick()
{
    m_deltaTime = (SDL_GetTicks() - m_lastTime) * (FPS / 1000.0f);

    if (m_deltaTime > DELTA_TIME)
    {
        m_deltaTime = DELTA_TIME;
    }
    m_lastTime = SDL_GetTicks();
}

float Timer::getDeltaTime()
{
    return m_deltaTime;
}