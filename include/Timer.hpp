#pragma once

#include <memory>

class Timer
{
public:
    virtual ~Timer() = default;
    static Timer &getInstance();
    void tick();
    float getDeltaTime();
    const int FPS = 60;
    const float DELTA_TIME = 1.5f;

private:
    Timer() = default;
    Timer(const Timer &object) = delete;
    Timer &operator=(const Timer &object) = delete;
    static std::unique_ptr<Timer> m_instance;
    float m_deltaTime;
    float m_lastTime;
};