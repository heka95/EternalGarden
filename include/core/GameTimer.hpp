#pragma once
#include "core/ECSTypes.hpp"

namespace Garden::Core
{
    class GameTimer
    {
    public:
        GameTimer();
        void update();
        float deltaTimeSeconds() const { return m_deltaTime; }
        float deltaTimeMS() const { return m_deltaTime * 1000.0f; }

    private:
        float m_factor = (ENGINE_UPDATE_SPEED / 1000.0f);
        float m_maxDeltaTime = 1.0f;
        float m_frameTime = 1000.0f / ENGINE_UPDATE_SPEED;
        float m_lastTime{0};
        float m_deltaTime{0};
    };
} // namespace Garden::Core