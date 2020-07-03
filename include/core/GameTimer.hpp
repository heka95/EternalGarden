#pragma once

namespace Garden::Core
{
    class GameTimer
    {
    public:
        GameTimer();
        void reset();
        void update();
        float deltaTimeSeconds() const { return m_deltaTime; }
        float deltaTimeMS() const { return m_deltaTime * 1000.0f; }

    private:
        unsigned int m_elapsedTick{0};
        float m_deltaTime{0};
        unsigned int m_startTick{0};
    };
} // namespace Garden::Core